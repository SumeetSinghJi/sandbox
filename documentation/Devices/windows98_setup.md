# TITLE

Windows 98 VM - with - Oracle VirtualBox Install instructions
Dated: 19/04/2024 by Sumeet Singh @ www.sumeet-singh.com


# IMPORTANT 

When restarting you will get a black screen error message saying cannot find windows
vserver.exe just press any key e.g. SPACE BAR to continue and wait


# PURPOSE

1. Setup Windows 98 Second Edition (SE) Virtual Machine (VM/Guest)
2. Setup a Shared folder between host and guest
3. Setup display adaptor for higher resolutions and colours: True32 colors
4. Setup Mouse speeds
5. Install Winzip
6. Show hidden files
7. Install DirectX 6.1
8. Install Visual Basic 3.0


# METHOD

1. On your host e.g, Windows 10/11 go to add or remove features and enable: SMB 1.0 file sharing then restart
2. Create a folder on your computer C:\ drive for best results e.g. c:\DOSGames, right click - properties - sharing - advanced sharing - FULL CONTROL
to everyone, record name e.g. \\MY-PC\DOSGames in Security tab add Everyone, give full permissions
3. On host device go to - Settings - Advanced sharing settings - private and public network enable file and printer/folder sharing - 
turn off password protected sharing and file sharing connections set to 40 or 56 bit encryption - Skip to step 10 if already built OS
4. Install Oracle Virtualbox
5. Create a new VM for Windows 98 SE OEM
Download a Windows 98 SE iso or use .iso file called "Windows 98 Second Edition"
In Settings section (you can always right click on it set to the following MAX attributes)
CPU: 1 CPU core (beyond this crashes)
RAM: 512 MB (beyond this crashes)
Storage: 40GB
Virtual Memory: 48MB MAX! - Higher levels will crash when updating Graphics driver to support 256 colors
Under Network set to: Bridged Adaptor
6. When installing use a official key named "Windows 98 SE OEM Key"
7. During installation when fails turn VM off.
Before starting in virtual box right click on VM - Settings - Storage - Floppy
- drive 0 - add floppy "patcher9x-0.8.50-boot.ima" by downloading from these instructions 
https://github.com/JHRobotics/patcher9x
8. run patch9x
select options 1 then continue, it will overwrite/patch the Windows 98 setup then go back to A:/ DOS Prompt
Turn Machine state off.
9. Remove floppy, restart VM and continue with installation, try restarting twice
if error again. Be patient.
10. To share the host folder with the Win 98 On Windows 98 Right click on 
Network Neighbourhood - Properties - login to Windows Login - Restart, for password field leave blank
11. Right click on Network Neighbourhood - Map Network Drive - Select any available or E:/
set the address above e.g. \\MY-PC\DOSGames
12. In Oracle Virtual Box, click on VM e.g. Windows98, click settings, shared folders, click icon or right click
and add shared folder - e.g. C:\Games\Win98sharedfolder, check Auto-mount, and click OK. 
13. Add a test file in now or later then Restart VM now and test or at end of these build steps and test
14. To have higher resolutions, and colours - Follow this video https://www.youtube.com/watch?v=WFTCazn199I
if you get errors remember to set Video Memory of VM to max 48MB. You may need to restart a few times to take
effect just continue and be patient.
NOTE: A good resolution setup for poor eyesight is: 640 x 480, colors, True Color [32 bit], then set
the Virtual Box VM scaling to 200%
15. Install Winzip from here https://archive.org/details/wz32v800_exe included here
16. If Folder options is missing from Control Panel do the below to see hidden files.
Click Start - Run - type: regedit (and hit enter): browse to here
HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer
find the HIDDEN key, double click and set value to: 1
save and restart
17. Missing VBRUNxxx.dll files. Download them here: https://archive.org/details/vbrunDLL
then from shared folder on Win98 VM move to folder: C:\Windows\System
18. To play older games install DirectX 6.1 found here: https://archive.org/details/microsoftdirectx6.1englishsetup
19. To play older games and for missing VBRUN300.dll files install Visual Basic 3.0:
https://archive.org/details/ms-vbpro-30