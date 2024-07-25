
___________________________________________________________________________

                        PI SETUP
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

4. OPTIONAL - FOR PI 5 BOOT FROM NVME M.2
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


___________________________________________________________________________

                            NAS SETUP
___________________________________________________________________________

ARM CPU doesn't support TrueNAS unfortunately and seeing as we would possibly want to install
other software ontop of this device such as Plex or Home Assistant, Open Media Vault provides
NAS like capabilities.

1. INSTALL OPEN MEDIA VAULT
```bash

```


___________________________________________________________________________

                            PLEX SETUP
___________________________________________________________________________

1. INSTALL PLEX
```bash

```

___________________________________________________________________________

                        HOME ASSISTANT SETUP
___________________________________________________________________________

1. INSTALL HOME ASSISTANT
```bash

```


