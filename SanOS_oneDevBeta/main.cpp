#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;
const int TASKBAR_HEIGHT = 55;

SDL_Texture* gearIcon = nullptr;

void renderText(const std::string& message, int x, int y, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
    if (!font || !renderer) return;
    SDL_Surface* surf = TTF_RenderText_Blended(font, message.c_str(), color);
    if (!surf) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (!texture) {
        SDL_FreeSurface(surf);
        return;
    }
    SDL_Rect rect = { x, y, surf->w, surf->h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
}

SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (!newTexture) {
        std::cerr << "Warning: Failed to load asset image at " << path << "! Error: " << IMG_GetError() << std::endl;
    }
    return newTexture;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return 1;
    if (TTF_Init() == -1) return 1;

    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) == 0) {
        SCREEN_WIDTH = dm.w;
        SCREEN_HEIGHT = dm.h;
    }

    SDL_Window* window = SDL_CreateWindow("SantiOS Desktop Environment",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 18);
    if (!font) {
        font = TTF_OpenFont("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 18);
    }

    gearIcon = loadTexture("assets/gear.png", renderer);

    bool running = true;
    bool start_menu_open = false;
    bool format_24hr = true; 
    SDL_Event event;
    SDL_Color whiteText = {255, 255, 255, 255};
    SDL_Color redText = {231, 76, 60, 255}; 

    int mouseX = SCREEN_WIDTH / 2;
    int mouseY = SCREEN_HEIGHT / 2;

    // Define fixed math targets for menu positions relative to screen bottom
    int menuTop = SCREEN_HEIGHT - TASKBAR_HEIGHT - 405;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) running = false;
            
            if (event.type == SDL_MOUSEMOTION) {
                mouseX = event.motion.x;
                mouseY = event.motion.y;
            }
            
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mx = event.button.x;
                int my = event.button.y;
                
                // 1. Start Menu Button Box Toggle
                if (mx >= 5 && mx <= 45 && my >= (SCREEN_HEIGHT - TASKBAR_HEIGHT)) {
                    start_menu_open = !start_menu_open;
                }
                
                // 2. Start Menu Option Click Targets
                else if (start_menu_open && mx >= 5 && mx <= 305) {
                    // Format Toggle Row Box (Checks if clicked directly on the format line height)
                    if (my >= (menuTop + 60) && my <= (menuTop + 90)) {
                        format_24hr = !format_24hr;
                    }
                    
                    // Shutdown Row Box (Checks if clicked directly on the shutdown line height)
                    else if (my >= (menuTop + 100) && my <= (menuTop + 130)) {
                        running = false; 
                    }
                }
                else {
                    // Clicking outside the menu closes it
                    start_menu_open = false;
                }
            }
        }

        // Background
        SDL_SetRenderDrawColor(renderer, 25, 35, 50, 255);
        SDL_RenderClear(renderer);

        // Taskbar
        SDL_Rect taskbar = {0, SCREEN_HEIGHT - TASKBAR_HEIGHT, SCREEN_WIDTH, TASKBAR_HEIGHT};
        SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
        SDL_RenderFillRect(renderer, &taskbar);

        // Start Button
        SDL_Rect logo_btn = {5, SCREEN_HEIGHT - TASKBAR_HEIGHT + 7, 40, 40};
        SDL_SetRenderDrawColor(renderer, 46, 204, 113, 255);
        SDL_RenderFillRect(renderer, &logo_btn);

        if (font) {
            renderText("San", 12, SCREEN_HEIGHT - TASKBAR_HEIGHT + 16, font, whiteText, renderer);

            std::time_t t = std::time(nullptr);
            std::tm* now = std::localtime(&t);
            std::stringstream ss;
            
            if (format_24hr) {
                ss << std::put_time(now, "%H:%M:%S"); 
            } else {
                ss << std::put_time(now, "%I:%M:%S %p"); 
            }
            
            int clockX = format_24hr ? SCREEN_WIDTH - 110 : SCREEN_WIDTH - 145;
            renderText(ss.str(), clockX, SCREEN_HEIGHT - TASKBAR_HEIGHT + 16, font, whiteText, renderer);
        }

        // Start Menu Drawer Layout
        if (start_menu_open) {
            SDL_Rect start_menu = {5, menuTop, 300, 400};
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); 
            SDL_RenderFillRect(renderer, &start_menu);
            
            if (font) {
                // Header (y: menuTop + 20)
                renderText("Settings Menu", 60, menuTop + 20, font, whiteText, renderer);
                
                // Format Toggle Button Option (y: menuTop + 65)
                std::string modeText = format_24hr ? "Switch to 12h Format" : "Switch to 24h Format";
                renderText(modeText, 20, menuTop + 65, font, whiteText, renderer);
                
                // Shutdown Button Option (y: menuTop + 105)
                renderText("Shutdown SantiOS", 20, menuTop + 105, font, redText, renderer);
            }

            if (gearIcon) {
                SDL_Rect gearRect = { 20, menuTop + 15, 30, 30 };
                SDL_RenderCopy(renderer, gearIcon, NULL, &gearRect);
            }
        }

        // Custom Mouse Cursor Rendering
        SDL_Rect cursor = { mouseX, mouseY, 12, 12 };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &cursor);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); 
    }

    if (gearIcon) SDL_DestroyTexture(gearIcon);
    if (font) TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}