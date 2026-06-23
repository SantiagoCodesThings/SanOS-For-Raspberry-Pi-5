## `HOW TO DOWNLOAD SANOS` 

```
SanOS 1 Developer Beta is a C++ file that is compatible only for the Raspberry
Pi 5. SanOS does not have its own .img to transfer into a MicroSD Card, so here
are the exact steps on how to run SanOS 1 Developer Beta.
```

## `1. Get Raspberry Pi OS Lite` 

## `THINGS NEEDED:` 

- `Raspberry Pi 5 (with a Raspberry Pi compatible monitor connected and power supply)` 

- `Any SDXC-compatible card reader USB 3.0 compatible (or Type-C)` 

- `Micro SD Card (with at least 32 GB available)` 

- `Micro SD Adapter` 

- `Latest version of Raspberry Pi Imager` 

- `Use Windows as your operating system for your PC or laptop. There will be Mac and Linux compatible soon.` 

```
        Go to https://www.raspberrypi.com/software/operating-systems/ and
download Raspberry Pi OS Lite (64-bit or 32-bit depending on your Pi hardware)
on your PC or laptop. The file format should be .img.
```

```
        Next, go to https://www.raspberrypi.com/software/ and download the
Raspberry Pi Imager (Windows) onto your PC or laptop and then complete the
“Wizard” to get the app.
```

```
        Insert the Micro SD Card and the Micro SD Adapter in the card reader,
and then plug the card reader into your PC or laptop. Open Raspberry Pi Imager
and follow these steps:
```

`1. Select your Raspberry Pi device as Raspberry Pi 5. Click next.` 

`2. Select “Use custom” as your operating system and select the .img file. Click next.` 

`3. Select your card reader as storage (it is recommended to unplug any external devices if you have any so that you will only see the card reader).` 

`4. BEFORE YOU WRITE THE IMAGE FILE, if you have any important data on your Micro SD Card already, either use an empty one (or one without important data) or transfer your important files into a secure, alternative storage. Click “Write” and confirm to write the image file.` 

`5. Wait for the writing process to finish, and then click “Finish.”` 

```
Now insert your Micro SD Card into your Raspberry Pi 5,  and sign up. Also, plug
in a physical USB mouse and keyboard directly into the Raspberry Pi 5’s USB
ports.
```

`2. Remote Access` 

```
THINGS NEEDED:
```

```
* Windows Terminal
```

```
        Open Windows Terminal on your PC/Laptop and type the following command
(replace username with the username you used to sign up on your Raspberry Pi and
replace pi_ip_address with your Raspberry Pi’s ip address, in which you need to
```

```
set up Wi-Fi for.):
```

```
        ssh username@pi_ip_address
```

```
Enter your Raspberry Pi’s password you set up when prompted. The terminal won’t
show any characters as you type, so blindly type in your Raspberry Pi’s password
and press enter. When you sign in, your Raspberry Pi’s terminal will be
connected to your Windows Terminal. Ensure that both devices are on the same Wi-
Fi.
```

```
        Now, you need to install the dependencies to run SanOS. Run the
following command in your Windows Terminal that is connected to the Raspberry
Pi’s terminal to install the graphics and font libraries:
```

```
        sudo apt update && sudo apt install -y build-essential libsdl2-dev
libsdl2-image-dev libsdl2-ttf-dev
```

`3. Compiling And Running` 

```
THINGS NEEDED:
```

- `Windows terminal (or SSH connection bridge)` 

```
* Raspberry Pi 5 (and it’s terminal)
```

```
        Open your terminal (or your SSH connection bridge) and type the
following command to move into the “SanOS_oneDevBeta” folder (in which you
extracted):
```

```
        cd SanOS_oneDevBeta
```

```
Once you are inside the folder, type ls in your terminal to verify that you have
an “assets” folder, “main.cpp” file, and the “README.md” file, in which you are
reading right now.
```

```
        SantiOS is written in C++ and uses the SDL2 graphics stack. To compile
the raw source code into a runnable application on your Pi, execute the
following build command:
```

```
        g++ main.cpp -o sanos -lSDL2 -lSDL2_image -lSDL2_ttf
```

```
This will instantly generate an executable binary file named “sanos” inside your
folder.
```

```
        Lastly, to run SanOS on to your Raspberry Pi’s terminal, run the
following command shown:
```

```
        SDL_VIDEODRIVER=kmsdrm SDL_INPUT_LINUXEV=1 ./sanos
```

```
This is the end of the instructions to run SanOS on your Raspberry Pi 5.
```

