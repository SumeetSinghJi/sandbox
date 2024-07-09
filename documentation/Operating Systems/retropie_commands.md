___________________________________________________________________________

                          RETROPIE SETUP
___________________________________________________________________________

ACCESS
```bash
ssh pi@IP_GOES_HERE
password %: raspberry
```

OPTIONAL - INSTALL FTP AND OPEN PORT 21 FOR FILE TRANSFER
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

ADD GAMES
1. Find the "Rom Folder" names for each emulator you want e.g. for Gameboy
the emulator Rom Folder name is "gb" from official docs - https://retropie.org.uk/docs/Game-Boy/ 
2. Make the folders on a USB and fill them with roms that you dumped from your own cartridges
3. Plug the USB into any USB slot of the raspberry pi and first see which usb folder it's in
e.g. /media/usb or usb1 - 4
4. Copy all the folders over
```bash
cp -r /media/usb1/* /home/pi/RetroPie/roms 
```

SWAP A/B BUTTONS
1. In main menu (core/emulator section) select RetroPie - RetroArch (will open a new menu) -
Settings - Input - Menu Controls
2. Set "Menu swap OK/Cancel buttons" to ON. This will change A/B buttons (or X/O on playstation controller)
3. Go back to Main menu - configuration - save current configuration
4. Done

SETUP HOTKEYS (TURBO + SAVE STATES + EMULATOR MENU)
1. In main menu (core/emulator section) select RetroPie - RetroArch (will open a new menu) -
Settings - Input - Hotkey Binds
2. scroll down to Hotkey - set to PS button on Playstation controller 
(e.g. the PS logo on Dualshock 5)
3. Select Fast Forward (Toggle) to be R3 (use in game with Press PS button + R3 (Hold down))
4. Menu toggle gamepad combo - select "Start + Select" (use in game with Press Start + Select)
5. Go back to Main menu - configuration - save current configuration
6. Done

SETUP BOTH ARCADE BUTTONS/JOYSTICK
# note you can keep a ps controller or keyboard 
# plugged in while setting up the 2 arcade sticks
# To setup any controller just hold down any button on it and it will detect
# just that controller, then setup any buttons and skip any you cant do
1. https://www.youtube.com/watch?v=uL3K8sZIuWo


ADD BIOS
(Necessary for PS1)
1. Find the BIOS somewhere e.g. by dumping your own consoles BIOS
1. Put all files (e.g. for PS1) in BIOS
cp scph5500.bin, scph5501.bin, scph5502.bin /home/pi/RetroPie/BIOS


CONSOLE BOOT SOUND
1. Edit config to set boot sound for whichever core e.g. ps1 to start
nano /opt/retropie/configs/all/retroarch-core-options.cfg
pcsx_rearmed_show_bios_bootlogo = "disabled"
# change to
pcsx_rearmed_show_bios_bootlogo = "enabled"


AUTO START (ENTER) GAME ON STARTUP

1. nano /opt/retropie/configs/all/autostart.sh
2. To start any rom on startup type/replace the core and rom path with the game 
e.g. the below will start Street Fighter 2 on Startup.
```bash
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
