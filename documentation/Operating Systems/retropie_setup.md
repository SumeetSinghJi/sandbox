___________________________________________________________________________

                        ARCADE1UP CABINET MODDING
___________________________________________________________________________

The steps below outline modding an Arcade1up cabinet to setup with retro
game emulation along with cosmetic changes.

The steps apply to Arcade1up generation 2 cabinets but you may pick and choose
whichever steps to apply to any arcade machine.

1. Add steel riser kickplate protection https://www.youtube.com/watch?v=Os-N8Orcxu8
There are 2 options steel riser options below; Test both and see your cosmetic 
preference
Option A: 30cm steel riser to complement existing riser
Option B: 60cm steel riser to replace existing riser 
2. Add real coin door https://www.youtube.com/watch?v=kSyySSv1ywQ
3. Add custom marquee
4. Follow video to build together https://www.youtube.com/watch?v=09DQCOr6zQM 
The final build should look like below assuming 6" steel riser

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
      +------------------------|
      |                        |
      |                        |      
      |                        |
      |                        |
      |    Steel Riser (12")   |
      |                        |
      +------------------------+
5. Follow steps below to setup retropie



___________________________________________________________________________

                          WHAT IS RETROPIE?
___________________________________________________________________________

If you want a gaming device like an arcade machine, or a custom gameboy
that has every retro game console and game in it you can take and play anywhere
then you need to install different emulators. RetroPie packages these steps in
a simple one click setup.

As per: https://www.reddit.com/r/RetroPie/comments/yet5v1/retropie_or_emulation_station/

For any Linux OS (not just RaspberryPi), RetroPie runs a bunch of scripts that
installs and configures; 
1. User account "pi" with all necessary permissions
2. Default drivers (if RaspberryPi)
3. Retroarch
4. All emulator cores (even for PS1 games to work without BIOS if not yet added)
5. All ROM folders, etc.,
6. Emulation Station (from git pull ./make not from apt)
7. Autoboot to "emulationstation" launcher

So you can see it does quite alot. If you want a dedicated linux emulator device
then best use RetroPie to automatically do it all.

If using Windows then you can just use Retroarch.

INSTALLING RETROPIE - https://retropie.org.uk/docs/First-Installation/

[Or just watch the YouTube video here](https://www.youtube.com/watch?v=E1sbnPZ_A8w)

___________________________________________________________________________

                          WHAT IS BIOS?
___________________________________________________________________________

For CD and up generation gaming consoles you will need to dump your consoles
operating system called a bios and add it to your emulators folder.

Conveniently they are available online but first ensure you legally own the console first. 
An example for illustration purposes are here: https://github.com/Abdess/retroarch_system/releases/


___________________________________________________________________________

                          RETROPIE SETUP
___________________________________________________________________________

1. INSTALLING FROM IMAGE
```bash
1. Use PI imager - Select Raspberry Pi OS - Select storage medium e.g, Micro SD Card - Enable SSH during setup - Enable Wifi and add login details - Install - Plug Micro SD card into Pi then done. 
2. Find the IP address of the Raspberry PI e.g. either from router or arp -a command if on same network 
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

10. SWAP A/B BUTTONS
a. In main menu (core/emulator section) select RetroPie - RetroArch (will open a new menu) -
Settings - Input - Menu Controls
b. Set "Menu swap OK/Cancel buttons" to ON. This will change A/B buttons (or X/O on playstation controller)
c. Go back to Main menu - configuration - save current configuration
d. Done

11. SETUP HOTKEYS (TURBO + SAVE STATES + EMULATOR MENU)
a. In main menu (core/emulator section) select RetroPie - RetroArch (will open a new menu) -
Settings - Input - Hotkey Binds
b. scroll down to Hotkey - set to PS button on Playstation controller 
(e.g. the PS logo on Dualshock 5)
c. Select Fast Forward (Toggle) to be R3 (use in game with Press PS button + R3 (Hold down))
d. Menu toggle gamepad combo - select "Start + Select" (use in game with Press Start + Select)
e. Go back to Main menu - configuration - save current configuration
f. Done

12. SETUP BOTH ARCADE BUTTONS/JOYSTICK
note you can keep a ps controller or keyboard plugged in while setting up the 2 arcade sticks
To setup any controller just hold down any button on it and it will detect
just that controller, then setup any buttons and skip any you cant do
a. https://www.youtube.com/watch?v=uL3K8sZIuWo


13. ADD BIOS
(Necessary for PS1)
a. Find the BIOS somewhere e.g. by dumping your own consoles BIOS
or here if you legally own the console: https://github.com/Abdess/retroarch_system/releases/
b. Put all files (e.g. for PS1) in BIOS
```bash
cp scph5500.bin, scph5501.bin, scph5502.bin /home/pi/RetroPie/BIOS
```

14. CONSOLE BOOT SOUND
a. Edit config to set boot sound for whichever core e.g. ps1 to start
```bash
nano /opt/retropie/configs/all/retroarch-core-options.cfg
pcsx_rearmed_show_bios_bootlogo = "disabled"
# change to
pcsx_rearmed_show_bios_bootlogo = "enabled"
```

15. OPTIONAL - START GAME ON BOOT
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

16. ADD GAME ARTWORK | THUMBNAIL IMAGES
a. In main menu where you select your emulators press start
b. Press scrapper
c. Press to configure by having user not worry about conflicts (automatically find images)
d. Press to start and it will download all images by itself
e. If Some images are skipped you can go back and choose the second scrapper which scraps images
from a different website and complete the remaining images

17. OPTIONAL - KEEP MOUSE LOCKED TO ACTIVE GAME SCREEN (NO BORDERLESS)
a. set hotkey mouse (toggle) to any button e.g. doubel quotation mark (").
in game press that button and mouse will lock to screen.