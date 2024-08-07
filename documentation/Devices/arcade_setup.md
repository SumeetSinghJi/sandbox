
# COMPLETE ARCADE/ARCADE1UP BUILD AND MOD GUIDE 2024

By: Sumeet Singh @ sumeet-singh.com

Date: August 2024

Description: This document outlines various ways to repair, build, modify, and setup with emulators/retro games various arcade machine cabinets.


# TABLE OF CONTENTS
- [1. Building Arcade machines](#building-arcade-machines)
- [2. Modifying Arcade1UP machines](#modifying-arcade1up-machines)
- [3. Emulator Setup](#emulator-setup)
- [4. Selling Arcade machines](#selling-arcade-machines)
- [5. Credits](#credits)


# BUILDING ARCADE MACHINES

Why collect, mod, or build arcade machines/cabinets? because they are fun and you learn lots of skills.

These steps outline how to build your own custom arcade machine from scratch either yourself or with a carpenters help
to cut the wood (machine) the parts so you can put together, as well as various ways to paint the cab. Once the cab is built
and all electronics added you can skip to the Retropie Setup steps to finally add retro game emulation on it

Benefits of building your own machine include being able to have 1 of each game type (e.g. Fighting, seated racing, or gun arcade cabinet)
that you can customise however you want.

If you feel this is too much effort you can always buy Arcade1UP arcade machines and use the below modding guide to customise.

NOTE: Arcade joystick cables are called "2.8mm Terminal Quick Connects" arcade cables.


### CRT VS MODERN TV e.g, LCD/LED/PLASMA

Many people choose to use older CRT (Cathode Ray Tube) style TV's to use in Arcade machines to get an authentic retro gaming experience.
Thus many people option for buying and installing a CRT TV. Although fun CRT TV's are not commercially viable and what parts exist
are usually heavy, expensive, rare and difficult to repair. Regardless the emulator software's dont care what screen you use so if you 
don't want the hastle of dealing with an old CRT TV theirs nothing wrong with using a modern style Flatscreen TV. Note the build guides below
have optional schematics for CRT retro style cabinets and modern flatscreen style.

Choose whichever CRT or LCD cabinet you prefer. Note CRT cabinets are bigger as they are meant to hold
the weight of the CRT TV and in general use older Retro style cabinets, whereas Flatscreen uses more flatscreen style.


### BUILDING STADING LIGHT GUN CABINET

First check the list of available games and if you feel it's adequte then follow steps below
https://en.wikipedia.org/wiki/List_of_light-gun_games

I have not yet investigated if the lightgun can be used as a controller to play non light gun fps/over the head shoulder style games e.g, 
Silent Hill/Resident Evil 2. __________________________________FILL ME_____________________________

Note that Raspberry Pi's are too slow to emulate perfect light gun latency games as reported by many Reddit users. Keep this in mind.

1. There are 2 types of light guns on the market, the calibration required but perfect Gun4IR, and the less responsive simple Sinden light guns 
https://www.sindenshop.com/, the best option is Gun4IR for even faster then CRT TV latency.

3. Get wood cut and ordered using the schematics here ____________________
4. Setup the computer with emulator following Emulator setup steps within this guide
5. Build the cabinet by following these steps:


### BUILDING SEATED RACING CABINET

1. Simplest option is to buy a "full motion racing cockpit simulator" by searching on Google e.g, https://dofreality.com/
2-axis is the cheapest and 6-axis full motion is the most expensive.
Consider using a universal option with both controls for Racing & Flying e.g, https://dofreality.com/product/universal/universal-motion-platform-6-axis-hero-h6/
2. Then add your TV, console/PC, connect it together

3. Get wood cut and ordered using the schematics here ____________________
4. Setup the computer with emulator following Emulator setup steps within this guide
5. Build the cabinet by following these steps:

### BUILDING GENERIC ARCADE CABINET

CRT cabinet final design example: https://www.youtube.com/watch?v=fl0FW4VvbNM
Flatscreen cabinet final design example: 

1. Buy Sanwa Joysticks - 
2. Buy Speakers - 
3. Buy arcade harness cables -
4. Buy real coin door -
5. (OPTIONAL) If using a modern PC/Raspberry Pi for emulation you will
need to buy a "HDMI to RCA Converter" to plug it into the CRT TV.
5. Get wood cut and ordered using the schematics here 
CRT: https://retromash.com/2015/01/02/building-a-home-arcade-machine-part-1/
Flatscreen: 
6. Setup the computer with emulator following Emulator setup steps within this guide
7. Build the cabinet by following these steps 
CRT: https://retromash.com/2015/01/02/building-a-home-arcade-machine-part-1/
Flatscreen: 
8. Test and done


# MODIFYING ARCADE1UP MACHINES

If you have an existing Arcade1up cabinet the following steps outline the ways to improve the cosmetic and functional aspects of it.
Once the cab is built and all electronics added you can skip to the Retropie Setup steps to finally add retro game emulation on it

1. ADD DIAMOND TREAD KICKPLATE
To protect the bottom of the arcade cabinet from being damaged from repeated kicks follow this guide https://www.youtube.com/watch?v=Wf4RVx3Bs-o

2. BUILD CUSTOM RISER

Size comparisons

Deluxe vs XL: https://www.reddit.com/media?url=https%3A%2F%2Fpreview.redd.it%2Fanyone-holding-out-for-the-2024-cabinets-im-hoping-for-more-v0-3aqwpaofk8ec1.png%3Fwidth%3D1756%26format%3Dpng%26auto%3Dwebp%26s%3D8ebaee4471a173ffbe9dc32f272372e33d3fa8d0
Deluxe vs Real original arcade: https://www.youtube.com/watch?v=jvMRYGZPh34

3/4 cabs: varies
Deluxe cab: 155cm
XL cab: 165cm + 3" wider

Both 3/4 and Deluxe cabinets share same length and width dimensions and fit same riser - https://www.reddit.com/r/Arcade1Up/comments/167qcsp/can_the_deluxe_cabinets_be_put_on_risers/ XL cabs are also authentic but they are huge. Deluxe provide the middle ground authentic footprint
arcade experience.

## FOR DELUXE CABINETS

### OPTION A - Flush riser

Buy a flush riser then put metal diamond tread kickplates on all sides to prevent wear and tear
Cons are it will cause balance instability and exhuberate the rocking issue with these top heavy tall cabs (serious consideration)
Prepurchase: https://www.gijoelgaming.com/product/arcade1up-inline-riser
Example: https://www.youtube.com/watch?v=wlPyo3gw3MA

      +------------------------+
      |     MORTAL KOMBAT      |
      |                        |
      +------------------------+
      | +--------------------+ |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | +--------------------+ |
      |                        |
      |------------------------|
      |   X O O O   X O O O    |
      |------------------------|
      |                        |
      |                        |
      |                        |
      |       +---------+      |
      |       |  |   |  |      |
      |       |  _   _  |      |
      |       | |_| |_| |      |
      |       +---------+      |
      |                        |
      |                        |
      |                        |
      |                        |
      |                        |
      |                        |     
      +------------------------+
      |    Flush Riser (4")    |
      |                        |
      +------------------------+

### OPTION B - non flush riser

Buy a no flush riser then put metal diamond tread kickplates on all sides to prevent wear and tear, base adss stability.
Prepurchase: https://www.buystuffarcades.com/products/mini-riser-for-deluxe-arcade1up-cabs

      +------------------------+
      |     MORTAL KOMBAT      |
      |                        |
      +------------------------+
      | +--------------------+ |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | +--------------------+ |
      |                        |
      |------------------------|
      |   X O O O   X O O O    |
      |------------------------|
      |                        |
      |                        |
      |                        |
      |       +---------+      |
      |       |  |   |  |      |
      |       |  _   _  |      |
      |       | |_| |_| |      |
      |       +---------+      |
      |                        |
      |                        |
      |                        |
      |                        |    
      |                        |
      |                        |
     +--------------------------+
     |   Metal Kickplate (4")   |
     |                          |
     +--------------------------+

## FOR 3/4 CABINETS

As Arcade1up 3/4 cabinets are too short by 15cm (6") by personal testing and most reports https://www.reddit.com/r/Arcade1Up/comments/sdjj7n/even_with_riser_arcade_games_are_not_high_enough/ we then add that to the
custom riser measurements below to either extend the existing riser by 15cm or make a new riser for 49cm;

Aracde modder example dimensions - breakdown - https://www.reddit.com/r/Arcade1Up/comments/hql8o3/riser_specs/
4 x Outer panels 51cm (l) x 34cm (h)
2 x Inner panels 48cm (l) x 29cm (h)
2 x Weight bearing panels 48cm (l) x 5cm (w)

### OPTION A - Buy Riser extender

Buy a riser extender (diamond kickplate pattern best) and use the dimensions

Prepurchase: https://www.buystuffarcades.com/products/riser-booster-for-arcade1up-arcades?variant=40523236540576
Example: https://www.youtube.com/watch?v=2bcejhZNyBA&lc=Ugzya6nEhq4Rz2VvC5F4AaABAg.A6OuP1Pj09KA6PBk7JDYHM

      +------------------------+
      |     MORTAL KOMBAT      |
      |                        |
      +------------------------+
      | +--------------------+ |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | +--------------------+ |
      |                        |
      |------------------------|
      |   X O O O   X O O O    |
      |------------------------|
      |                        |
      |                        |
      |                        |
      |       +---------+      |
      |       |  |   |  |      |
      |       |  _   _  |      |
      |       | |_| |_| |      |
      |       +---------+      |
      |                        |
     +--------------------------+
     |                          |
     | Arcade1up Riser (13.25") |      
     |                          |
     |                          |     
     +--------------------------+
     |     Custom Riser (4")    |
     |                          |
     +--------------------------+

### OPTION B: Build custom riser

Example here https://www.youtube.com/watch?v=B4P6Nuofftg

      +------------------------+
      |     MORTAL KOMBAT      |
      |                        |
      +------------------------+
      | +--------------------+ |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | |                    | |
      | +--------------------+ |
      |                        |
      |------------------------|
      |   X O O O   X O O O    |
      |------------------------|
      |                        |
      |                        |
      |                        |
      |       +---------+      |
      |       |  |   |  |      |
      |       |  _   _  |      |
      |       | |_| |_| |      |
      |       +---------+      |
      |                        |
     +--------------------------+
     |                          |
     |   Custom Riser (13.25")  |      
     |                          |
     |                          |     
     +--------------------------+

3. LIGHT UP COIN DOOR
https://www.youtube.com/watch?v=lsZ99HHl2U0

4. ADD REAL COIN DOOR
First purchase an "2.8mm Terminal Quick Connects split arcade cables" then follow this guide https://www.youtube.com/watch?v=kSyySSv1ywQ

5. ADD CUSTOM LIT MARQUEE

6. FIX LOW LEVEL SPEAKER STATIC
The static can be fixed, I bought a better quality 12v power supply off Amazon and a TRRS Male to Female Stereo Audio Jack Extender Aux Extension Adapter Cords with Volume Control. Its a pain that they have the gain too high off the PCB and a noisy power supply, this way I can turn the gain down manually and it lowers the noise floor. The other fix is the reroute the headphone jack which is line level out and connect the speakers to that but I wanted to be able to still use headphones. It is kinda weird / lazy that they have not fixed an annoying problem that has a relatively cheap fix. - Youtube commenter @user-pi6cs3ue4s August 2024 https://www.youtube.com/watch?v=alf4X3mJsHQ

7. ADD LINK CABLE FOR MULTIPLAYER
https://www.buystuffarcades.com/products/ridge-racer-and-outrun-mod-kit

8. REPLACE JOYSTICK BUTTONS
You can choose to replace the stock cheap Arcade1up buttons on the non XL models with better products. You will need to buy
Sanwa style arcade buttons
1. Follow this to replace buttons - https://www.youtube.com/watch?v=09DQCOr6zQM

9. ADD BIGGER SCREEN
To add a different size monitor or TV to an existing Arcade1up cabinet such as increasing the screen size for shooter games
you need the below;
1 x Geekworm HDMI to LDVS 20 (a.k.a 2.0) adapter - https://geekworm.com/products/lvds-to-hdmi-adapter-board-converter-with-lvds-cable
1 x HDMI cable
1 x TV/Monitor
1 x VEGA bracket support frame
STEPS
a. Disconnect the Arcade1up PCB board from the stock monitor and connect to LDVS conveter in Channel 1
ensure the twisted ribbon style cable you connect has the dot on it's plastic seated in the same PCB dot reference (PIN 1)
Optionally, Seperate the board from the LCD with cardboard and double sided tape to prevent electrial shorting
b. add HDMI cable to LDVS and TV and turn on game and test. If flickering/drop outs occour then test with Channel 2 position
d. Once desired position is kept add the Wood/VEGA frame to Arcade cabinet and TV and connect all back together and test

10. COMPLETE BUILD GUIDE - RASPBERRY PI + SPEAKERS + BUTTONS
https://www.youtube.com/watch?v=09DQCOr6zQM



# EMULATOR SETUP

If you want an graphical software that has emulators that represent various game consoles to play games on such as Atari, or Sega, then
you need to generally install a software like "Retroarch". Retroarch can be installed on many operating systems such as windows, mac or
various linux distrobutions and allows you to download various consoles such as Sega Megadrive within it. After that's done you can 
point to a file location containing various games known as roms, setup key bindings, set to download game artwork and launch Retroarch
and get started choosing a retro or modern game console and game to play. The guide below advises how to setup Retroarch on Windows, Mac
and Linux distro's and get BIOS for game consoles.  We do not condone piracy of games. If you require games (roms) then you will need to 
research yourself (try asking AI).

### BIOS

What is a BIOS and why is it needed?

BIOS represent the Operating System of a console. Old retro consoles like gameboys don't have an OS like modern consoles
such as Playstation, therefore retro console emulators can run games without a need for a BIOS.

To obtain a bios requires dumping (extracting) the files from your existing console. Considering you own the consoles
already you can conveniently find a list of all BIOS needed for Retroarch here: https://github.com/Abdess/retroarch_system/releases/

Simply download the files (called a BIOS set) and add them to the respective folder required after Retroarch (or any emulator) is installed.

### WINDOWS

Install Retroarch from here: https://www.retroarch.com/

### MAC

Install Retroarch from here: https://www.retroarch.com/

### LINUX

Setting up Retroarch on Linux is often difficult and time consuming, you can choose to setup yourself using below link
Install Retroarch from here: https://www.retroarch.com/ 
or use Retropie which runs on may Linux distro's (not just Raspberry Pi) which runs a bunch of scripts that installs and configures; 
1. User account "pi" with all necessary permissions
2. Default drivers (if RaspberryPi)
3. Retroarch
4. All emulator cores (even for PS1 games to work without BIOS if not yet added)
5. All ROM folders, etc.,
6. Emulation Station (from git pull ./make not from apt)
7. Autoboot to "emulationstation" launcher

So you can see it does quite alot. If you want a dedicated linux emulator device
then best use RetroPie to automatically do it all.

#### RETROPIE SETUP STEPS

1. INSTALLING FROM IMAGE
```bash
1. Use PI imager - Select Raspberry Pi OS - Select storage medium e.g, Micro SD Card - Enable SSH during setup - Enable Wifi and add login details - Install - Plug Micro SD card into Pi then done. 
2. Find the IP address of the Raspberry PI e.g. either from router or arp -a command if on same network 
```

OPTIONAL. CHANGING WIFI PASSWORD
```bash
/etc/wpa_supplicant/wpa_supplicant.conf # edit this file

network={
    ssid="YourNetworkName" # update this with your wifis name
    psk="YourPassword" # add your wifis password here
}
```

2. ACCESS PI VIA SSH
```bash
ssh pi@IP_GOES_HERE
password %: raspberry
```

3. UPDATE PI
```bash
sudo apt update
sudo apt upgrade -y
```

5. OPTIONAL - FOR PI 5 BOOT FROM NVME M.2
```bash
a. Connect a compatible m.2 hat for the Pi 5 and add connect NVME m.2 storage media and to the pi
b. In Raspberry Pi imager "you can reopen it if you closed it" click Storage then select the NVME m.2 storage media
follow instructions
c. sudo raspi-config
d. Advanced Options
e. Boot Order
f. NVME/USB Boot
g. sudo nano /boot/firmware/config.txt
h. insert line below
dtparam=pciex1_gen3
i. sudo reboot now
```

7. INSTALL RETROPI
```bash
cd
git clone --depth=1 https://github.com/RetroPie/RetroPie-Setup.git
cd RetroPie-Setup
sudo ./retropie_setup.sh
```

8. OPTIONAL - INSTALL FTP AND OPEN PORT 21 FOR FILE TRANSFER
```bash
sudo apt install vsftpd
sudo nano /etc/vsftpd.conf
Uncomment local_enable=YES # to allow local users to log in.
Uncomment write_enable=YES # to allow write access to the FTP server.
netstat -tuln # check if port now open
pi@retropi:~ $ tcp6       0      0 :::21                   :::*                    LISTEN 

# TO TRANSFER GAMES YOU CAN USE 
# WINDOWS = FILEZILLA
# MACOS = ???
```

9. ADD GAMES
IMPORTANT: PS2 games come in single .iso (DVD games) or a older 2 files together .bin/.cue (CD-ROM) style
a. Find the "Rom Folder" names for each emulator you want e.g. for Gameboy
the emulator Rom Folder name is "gb" from official docs - https://retropie.org.uk/docs/Game-Boy/ 
b. Make the folders on a USB and fill them with roms that you dumped from your own cartridges
c. Plug the USB into any USB slot of the raspberry pi and first see which usb folder it's in
e.g. /media/usb or usb1 - 4
d. Copy all the folders over
```bash
cp -r /media/usb1/* /home/pi/RetroPie/roms 
```

10. ADD BIOS
(Necessary for PS1)
a. Find the BIOS somewhere e.g. by dumping your own consoles BIOS
or here if you legally own the console: https://github.com/Abdess/retroarch_system/releases/
b. Put all files (e.g. for PS1) in BIOS
```bash
cp scph5500.bin, scph5501.bin, scph5502.bin /home/pi/RetroPie/BIOS
```

11. CONSOLE BOOT SOUND
a. Edit config to set boot sound for whichever core e.g. ps1 to start
```bash
nano /opt/retropie/configs/all/retroarch-core-options.cfg
pcsx_rearmed_show_bios_bootlogo = "disabled"
# change to
pcsx_rearmed_show_bios_bootlogo = "enabled"
```

12. OPTIONAL - START GAME ON BOOT | BOOT INTO GAME | AUTOSTART GAME
```bash
nano /opt/retropie/configs/all/autostart.sh
# To start any rom on startup type/replace the core and rom path with the game 
/opt/retropie/supplementary/runcommand/runcommand.sh 0 _SYS_ mame-libretro ~/RetroPie/roms/mame-libretro/sf2ce.zip &&$
# emulationstation #auto
```
To reverse comment the top and uncomment the bottom.
```bash
pi@retropie:~ $ cat /opt/retropie/configs/all/autostart.sh
# /opt/retropie/supplementary/runcommand/runcommand.sh 0 _SYS_ mame-libretro ~/RetroPie/roms/mame-libretro/sf2ce.zip && emulationstation
emulationstation #auto
pi@retropie:~ $
```

### RETROARCH CONFIGURATION

1. SWAP A/B BUTTONS
a. In main menu (core/emulator section) select RetroPie - RetroArch (will open a new menu) -
Settings - Input - Menu Controls
b. Set "Menu swap OK/Cancel buttons" to ON. This will change A/B buttons (or X/O on playstation controller)
c. Go back to Main menu - configuration - save current configuration
d. Done

2. SETUP HOTKEYS (TURBO + SAVE STATES + EMULATOR MENU)
a. In main menu (core/emulator section) select RetroPie - RetroArch (will open a new menu) -
Settings - Input - Hotkey Binds
b. scroll down to Hotkey - set to PS button on Playstation controller 
(e.g. the PS logo on Dualshock 5)
c. Select Fast Forward (Toggle) to be R3 (use in game with Press PS button + R3 (Hold down))
d. Menu toggle gamepad combo - select "Start + Select" (use in game with Press Start + Select)
e. Go back to Main menu - configuration - save current configuration
f. Done

3. SETUP BOTH ARCADE BUTTONS/JOYSTICK
note you can keep a ps controller or keyboard plugged in while setting up the 2 arcade sticks
To setup any controller just hold down any button on it and it will detect
just that controller, then setup any buttons and skip any you cant do
a. https://www.youtube.com/watch?v=uL3K8sZIuWo

4. ADD GAME ARTWORK | THUMBNAIL IMAGES
a. In main menu where you select your emulators press start
b. Press scrapper
c. Press to configure by having user not worry about conflicts (automatically find images)
d. Press to start and it will download all images by itself
e. If Some images are skipped you can go back and choose the second scrapper which scraps images
from a different website and complete the remaining images

17. OPTIONAL - KEEP MOUSE LOCKED TO ACTIVE GAME SCREEN (NO BORDERLESS)
a. set hotkey mouse (toggle) to any button e.g. doubel quotation mark (").
in game press that button and mouse will lock to screen.


# SELLING ARCADE MACHINES

1. IF USING LINUX CLEAR WIFI PASSWORD
```bash
/etc/wpa_supplicant/wpa_supplicant.conf # edit this file

network={
    ssid="YourNetworkName" # Remove your Wifi name
    psk="YourPassword" # Remove your wifi password
}
```


# CREDITS

      Thanks to everyone in the Arcade1UP Reddit & YouTube community for keeping this hobby alive.

      Thanks to the dedicated Arcade1UP staff who go above and beyond to give us the best product possible. We wouldn't be here without you.

      Thanks to my canine companion Porus for always being there for me.

      And finally thanks to people like you that read this and continue to keep the hobby alive for others to experience.
