___________________________________________________________________________

                          RETROPIE SETUP
___________________________________________________________________________

OPTIONAL - INSTALL FTP AND OPEN PORT 21 FOR FILE TRANSFER
```bash
sudo apt install vsftpd
sudo nano /etc/vsftpd.conf
Uncomment local_enable=YES # to allow local users to log in.
Uncomment write_enable=YES # to allow write access to the FTP server.
netstat -tuln # check if port now open
pi@retropi:~ $ tcp6       0      0 :::21                   :::*                    LISTEN 
```

CHANGE A / B

Under RetroPie - RetroArch - buttons


SETUP BOTH ARCADE BUTTONS/JOYSTICK

# note you can keep a ps controller or keyboard 
# plugged in while setting up the 2 arcade sticks
# To setup any controller just hold down any button on it and it will detect
# just that controller, then setup any buttons and skip any you cant do
1. https://www.youtube.com/watch?v=uL3K8sZIuWo


ADD BIOS

(Necessary for PS1)
1. Download the full retropi BIOS set from here: https://github.com/Abdess/retroarch_system/releases/
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
