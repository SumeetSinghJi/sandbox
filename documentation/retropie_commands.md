___________________________________________________________________________

                          RETROPIE SETUP
___________________________________________________________________________

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
