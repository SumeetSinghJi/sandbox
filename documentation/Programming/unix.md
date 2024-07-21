___________________________________________________________________________

                            REQUIREMENTS
___________________________________________________________________________

The commands below target the Debian family e.g. Debian, Ubuntu, RaspberryPi
however they can be modified with a quick confirmation with chatGPT to suit
other OS.

___________________________________________________________________________

                            FIRST TIME SETUP
___________________________________________________________________________


1. INSTALLING LINUX
```bash
1. Connect a USB storage to host
2. Download Ubuntu server
3. Download UNetbootin - start - select above image - select previous usb - ok
4. Connect USB to Hardware to install linux on - boot to BIOS e.g. CTRL-F12 - select boot options boot from EFI USB Device - save and exit
5. Setup Wifi once in
```

3. ADMINS
```bash
su
usermod -aG sudo vboxuser # or wheel group
cat /etc/sudoers
exit
sudo reboot # necessary to reset admin cache
```

4. UPDATE
```bash
sudo apt update
sudo apt upgrade -y
sudo apt dist-upgrade -y
sudo reboot
# or
pacman -Syu
```

5. DRIVERS
```bash
dmesg # check kernel for hardware/driver errors then fix/install
```

6. SSH
```bash
sudo apt install openssh-server -y # for incomming SSH
```

7. HARDEN
```bash
sudo apt install ufw
sudo ufw enable
sudo ufw allow ssh
sudo ufw status
```

8. OPTIONAL - GUI
```bash
sudo apt install ubuntu-desktop # ubuntu, or for low OS spec hardware install lubuntu-desktop
```

9. OPTIONAL - ENABLE INLINE COMMENTS
```bash
testusr@ubuntu Documents % setopt interactive_comments # zsh shell only
```

10. OPTIONAL - USEFULL PACKAGES
```bash
sudo apt install lolcat, git, flatpak
```

11. OPTIONAL - SETUP C/C++ COMPILER
```bash
# 1. INSTALL USEFULL PACKAGES 
sudo apt install -y build-essential g++ libboost-all-dev libcurl4-gnutls-dev 
libzip-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev 
zlib1g-dev googletest libgtest-dev yasm cmake git
# 2. Test C code
echo "#include <stdio.h>" > test.c
echo 'int main() { printf("Hello, world!\\n"); return 0; }' >> test.c
gcc -o test test.c
./test
```

12. CLEANUP
```bash
sudo snap remove firefox
```

___________________________________________________________________________

                        SHELL STARTUP SCRIPT
___________________________________________________________________________

Your startup scripts, environmental variables, alias and more are documented
in your shell script located under /home/username/ hidden found with "ls -la"
They need to be added there and the shell restarted for the change to take 
place. There are 3 or more shell's usually e.g, ~/.zshrc, ~/.bash or 
~/.bash_profile. edit 1 to include the envionmental variable as per below 
steps, and remove any outdated version form the other shell scripts for MacOS 
add the path only to: ~/.zshrc

1. Open your shells startup script
```bash
open -e ~/.zshrc # MacOS only? Please confirm this also works on Ubuntu or not
# or
sudo nano ~/.zshrc
```

2. Add your startup code
```bash
sumeetsingh@Sumeets-Air-2 sandbox % cat ~/.zshrc   
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
export PATH="/opt/homebrew/Cellar/ruby/3.3.2/bin:$PATH" # brew install ruby

# ZSH SHELL ONLY
setopt interactive_comments # enables inline CLI comments in zsh with # e.g. % echo test # test comment

runlolcat() {
    local cmd="$1"
    shift
    command "$cmd" "$@" 2>&1 | lolcat
}

# Aliases
alias ls='runlolcat ls'
alias cat='runlolcat cat'
alias grep='runlolcat grep'
alias tail='runlolcat tail'
alias head='runlolcat head'
```


___________________________________________________________________________

                    COMMON COMMANDS
___________________________________________________________________________

SSH
e.g. by remoting into raspberry pi with default u: pi p: rasbperry
```bash
ssh pi@192.168.0.211
pi@retropi:~ enter password $ raspberry
```

FIND DISTRIBUTION | RELEASE | VERSION
```bash
cat /etc/os-release
```

QUITTING CLI
```bash
# option 1
press "ESC" then "w" then "q"

# option 2
q
```

NAVIGATION FILTERING
```bash
#pipe through | less
apt list --installed | grep es | less # quit with q
pi@retropie: ~ $ q # at END press q
```

MOVE CLI / TERMINAL PROMPT TO TOP OF SCREEN AGAIN
```bash
clear
```

COMMENTS
```bash
# Zsh shell only - enable inline comments with setopt
testusr@ubuntu Documents % setopt interactive_comments
testusr@ubuntu Documents % echo test # test
test

cd c:\users\sumeetsingh\Documents ; # in CLI use line break ; followed by comment
```

SEARCH - USERS
```bash
cat /etc/passwd # linux
# or
dscl . list /Users # macos
```

SEARCH - FILES
```bash
find /usr -iname "*xxx*"
ls | grep xxx
```

SEARCH - STRING
```bash
# use awk to pattern match strings in file
awk 'pattern { action }' file

# EXAMPLE
sumeetsingh@Sumeets-Air-2 sandbox % cat CREDITS.txt                  
2D asset images from: https://2minutetabletop.com/product-category/free/
Hourglass icon by icon-icons.com @ icon-icons.com/icon/sand-clock-hourglass/191332%                                          
sumeetsingh@Sumeets-Air-2 sandbox % awk '/asset/ { print }' CREDITS.txt # <-- LOOK HERE

2D asset images from: https://2minutetabletop.com/product-category/free/
```

SEARCH - PACKAGE MANAGER
```bash
pacman -Ss xxxxx
sudo apt search xxxx
sudo apt list --installed xxxxx
```

SEARCH - SERVICES
```bash
# 3 methods are below
# 1 - through apt
apt list --installed
# 2 - through system services
systemctl list-unit-files
# 3 through manual clone/make/install etc., the binary will be put in /bin and usually in environmental variable
ls /usr/bin 
emulationstation
pi@retropi:~ $ emulationstation # to then start it
```

PROCESS
```bash
top
htop # better version
```

SERVICES
```bash
sudo systemctl status ssh # check ssh service status
sudo systemctl start ssh # restart service if off
sudo systemctl enable ssh # enable service at boot
```

HARDWARE | DRIVER | KERNELL MESSAGES
```bash
dmesg
dmesg -w # for listen for new prompts
dmesg | grep usb # to filter for specific things
```

FIND BIN ENVIRONMENTAL VARIABLE
```bash
sumeetsingh@Sumeets-Air-2 which ruby
# or 
sumeetsingh@Sumeets-Air-2 where ruby
/usr/bin/ruby
```

FORMAT
```bash
ls | sort -h
```

LOGONS
```bash
w

# EXPLANATION
# The same user pi is logged in twice, once through hardware, once through SSH
# TTY = hardware sessions, therefore TTY1 means user is logged in through hardware on first port
# pts = Virtual terminal sessions such as through SSH, therefore pts/0 = a user is logged in through first remote session i.e SSH
pi@retropie:~ $ w
 17:59:46 up 35 min,  2 users,  load average: 0.42, 0.44, 0.38
USER     TTY      FROM             LOGIN@   IDLE   JCPU   PCPU WHAT
pi       tty1     -                17:24   35:11  10:29  10:28  /opt/retropie/supplementary/emulationstation/emulations
pi       pts/0    192.168.0.115    17:47    2.00s  0.30s  0.01s w
```

PERMISSIONS - USER GROUPS
```bash
id pi

# EXAMPLATION
# user "pi" is the first non root user = id 1000. They are also part of sudo group 27. etc.,
# So permissions below are for a standard user 'pi' for a raspberrypi AIO computer.
pi@retropie:~ $ id pi
uid=1000(pi) gid=1000(pi) groups=1000(pi),4(adm),20(dialout),24(cdrom),27(sudo),29(audio),44(video),46(plugdev),60(games),100(users),105(input),109(netdev),999(spi),998(i2c),997(gpio)


# NOTE: You can check your own group by just typing
groups
```

PERMISSIONS - FILE ACCESS
```bash
# e.g, making a simple script and granting file access to run
echo '#!/bin/zsh' > test.sh && echo 'figlet HELLO WORLD | lolcat' >> test.sh
# NOTE: chmod stands for Change Mode
chmod a+rwx test.sh # a = anyone, rwx = can read write execute

# you can use a (anyone), g (group), u (user), or o )others∂

# you can also target the current user without specifying a specific user
chmod +rwx
# or
chmod +x # just to give execute permissions e.g. for a cron job to yourself when logged in

# REMOVE PERMISSIONS
# do the opposite with a substraction (minus) character
chmod a-rwx

# GROUP ACCESS
# to give access based on a group e.g. you want anyone in piusers to be able to run script then
# first change the group ownership of the file to group
sudo chgrp piusers test.sh
chmod g+rwx test.sh

sumeetsingh@Sumeets-Air-2 sandbox % ./test.sh
 _   _ _____ _     _     ___   __        _____  ____  _     ____  
| | | | ____| |   | |   / _ \  \ \      / / _ \|  _ \| |   |  _ \ 
| |_| |  _| | |   | |  | | | |  \ \ /\ / / | | | |_) | |   | | | |
|  _  | |___| |___| |__| |_| |   \ V  V /| |_| |  _ <| |___| |_| |
|_| |_|_____|_____|_____\___/     \_/\_/  \___/|_| \_\_____|____/ 
```

SHUTDOWNS
```bash
sudo shutdown now
# or
sudo reboot now
```

FIND PHYSICAL DISPLAY
```bash
sudo systemctl status display-manager
```

DISK FREE | DISK SPACE | DISK USAGE
```bash
 # this works on the current directory you are in
 # -h = human readable format converts the bytes to MB's
 # -d = depth, to show the subdirectories sizes within
 # -c = total = total size of this folder so ./sandbox = ~300MB's
df -h 
du -h -d 1

sumeetsingh@Sumeets-Air-2 sandbox % du -hc -d 1

188K    ./documentation
 47M    ./etc
8.0K    ./vedic
8.0K    ./headers
4.0K    ./templates
114M    ./.git
 12K    ./.vscode
130M    ./assets
  0B    ./src
292M    .
292M    total
```

COPY FILES
```bash

# rsync VS cpp

# rsync only overwrites the existing destination file if they are different (sizes, types, etc.,) however with --ignore-existing it wont
# rsync can be resumed
# rsync is more network fault tolerant

# cp is faster

# CP

# use -i for confirmation before overwriting
# use -r to recurse and target contents inside folders
# use -v for verbose - best option
cp "/media/usb1/Silent Hill" /home/pi/RetroPie/roms/psx/ # COPY AND REPLACE 1 FILE
cp -rv /media/usb1/* /home/pi/RetroPie/roms/psx/ # COPY AND REPLACE ALL FOLDERS
cp -irv /media/usb1/* /home/pi/RetroPie/roms/psx/ # COPY AND ASK PERMISSION BEFORE OVERWRITING ALL FOLDERS
cp -r * ../ # COPY FOLDER CONTENTS TO PARENT
# OR use absolute path 
cp -r * /home/username/destination/  # COPY FOLDER CONTENTS TO PARENT
find . -mindepth 1 -maxdepth 1 -type d -exec cp -v -r {}/\* ../ \; # FROM PARENT DIRECTORY COPY ALL FOLDERS CONTENTS TO PARENT

# RSYNC

# use -a "archive mode" to preserve permissions, timestamps, symbolic links and other attributes of contents
# use --progress for a progress indicator
# use --ignore existing to now overwrite files that exist in destination
rsync -av --progress /media/usb1/* /home/pi/RetroPie/roms/psx/ # copy files and overwrite if different sizes
rsync -av --progress --ignore-existing /media/usb1/* /home/pi/RetroPie/roms/psx/ # copy files and dont overwrite
```

MOVE FILES
```bash
# use -i for confirmation before overwriting
mv "/media/usb1/Silent Hill" /home/pi/RetroPie/roms/psx/ # MOVE 1 FILE
mv -rv /media/usb1/* /home/pi/RetroPie/roms/psx/ # MOVE ALL FOLDERS
mv -irv /media/usb1/* /home/pi/RetroPie/roms/psx/ # MOVE ALL FILES + ASK BEFORE OVERWRITING
mv -r * ../ # COPY FOLDER CONTENTS TO PARENT
# OR use absolute path 
mv -r * /home/username/destination/  # COPY FOLDER CONTENTS TO PARENT
find . -mindepth 1 -maxdepth 1 -type d -exec sh -c 'mv -v -t ../ "$1"/* && rmdir "$1"' sh {} \; && rmdir ./*
 # FROM PARENT DIRECTORY COPY ALL FOLDERS CONTENTS TO PARENT THEN DELETE EMPTY SUBDIRECTORIES
rsync -av --progress --ignore-existing /media/usb1/ /home/pi/RetroPie/roms/psx/ && rm -rf /media/usb1/* # move and delete source directories/files skipping existing
scp diablo.bin diablo.cue pi@retropie:/home/pi/RetroPie/roms/psx # secure-copy from host to dest using port 22
sftp pi@retropie ; cd /home/pi/RetroPie/roms/psx ; put file1.txt ; exit # similar to scp but more steps
```

RENAME
```bash
mv -r /home/me/oldName /home/me/newName  # just use move with recurse to same location
```

RESOLUTION CHANGE
```bash
# If os doesn't fit inside the window e.g. a Retropi in an arcade cabinet
# has the bottom screen e.g. the text CLI prompt part cut off, then
# adjust the padding/overlay
sudo nano /boot/config.txt
# uncomment the below and the higher the number the more it moves in so
overscan_left=5 # padding 5 from left
overscan_bottom=60 # padding from the bottom
# if using nano
# CTRL - X
# Y
# PRESS ENTER
# done. If error, then close file and run with sudo
sudo reboot now # then view screen, test and adjust accordingly
```

SCRIPTING
```bash
# use 2 greater then symbols to use a new line, and use 1 to truncate
sumeetsingh@Sumeets-Air-2 sandbox % echo '#!/bin/zsh' > test.sh && echo 'figlet HELLO WORLD | lolcat' >> test.sh
sumeetsingh@Sumeets-Air-2 sandbox % chmod a+rwx test.sh
sumeetsingh@Sumeets-Air-2 sandbox % ./test.sh
 _   _ _____ _     _     ___   __        _____  ____  _     ____  
| | | | ____| |   | |   / _ \  \ \      / / _ \|  _ \| |   |  _ \ 
| |_| |  _| | |   | |  | | | |  \ \ /\ / / | | | |_) | |   | | | |
|  _  | |___| |___| |__| |_| |   \ V  V /| |_| |  _ <| |___| |_| |
|_| |_|_____|_____|_____\___/     \_/\_/  \___/|_| \_\_____|____/ 
```

CRON JOBS
```bash
cat << 'EOF' > /path/to/test.sh # 1. Write script
#!/bin/bash
echo "Hello, this is a test script executed by cron job" >> /path/to/test.log
EOF

chmod +x /path/to/test.sh # 2. make script executable

# export EDITOR=nano  # Set your preferred editor (nano, vi, etc.)
crontab -e << 'CRONJOB' # 3. add new cron job
# Example: Run test.sh every day at 9 AM
0 9 * * * /path/to/test.sh
CRONJOB

crontab -l # 4. verify cronjob

crontab -e # 5. reschedule job
```

FIND ALL OPEN PORTS
```bash
netstat -tuln

Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State      
tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN     
tcp        0      0 0.0.0.0:445             0.0.0.0:*               LISTEN     
tcp        0      0 0.0.0.0:139             0.0.0.0:*               LISTEN         
tcp6       0      0 :::22                   :::*                    LISTEN     
tcp6       0      0 :::445                  :::*                    LISTEN     
tcp6       0      0 :::139                  :::*                    LISTEN     
udp        0      0 0.0.0.0:37819           0.0.0.0:*                          
udp        0      0 0.0.0.0:68              0.0.0.0:*                          
udp        0      0 192.168.0.255:137       0.0.0.0:*                          
udp        0      0 192.168.0.211:137       0.0.0.0:*                          
udp        0      0 0.0.0.0:137             0.0.0.0:*                          
udp        0      0 192.168.0.255:138       0.0.0.0:*                          
udp        0      0 192.168.0.211:138       0.0.0.0:*                          
udp        0      0 0.0.0.0:138             0.0.0.0:*                          
udp        0      0 0.0.0.0:5353            0.0.0.0:*                          
udp6       0      0 :::546                  :::*                               
udp6       0      0 :::5353                 :::*                               
udp6       0      0 :::36174                :::* 
```

OPEN PORT 21 - INSTALL FTP
```bash
sudo apt install vsftpd
sudo nano /etc/vsftpd.conf
Uncomment local_enable=YES # to allow local users to log in.
Uncomment write_enable=YES # to allow write access to the FTP server.
netstat -tuln # check if port now open
pi@retropi:~ $ tcp6       0      0 :::21                   :::*                    LISTEN 
```

RENEW/RELEASE IP
```bash
sudo dhclient # RENEW ALL DHCP LEASES
sudo dhclient -r # RELEASE
sudo dhclient -r wlan0 # CHOOSE INTERFACE
```

RESTART NETWORKING SERVICE
```bash
sudo systemctl restart networking
sudo systemctl restart dhcpcd
```

USING NMAP
```bash
winget install nmap # windows
sumeetsingh@Sumeets-Air ~ %brew install nmap # mac

sumeetsingh@Sumeets-Air ~ % nmap -n 192.168.0.211
Starting Nmap 7.95 ( https://nmap.org ) at 2024-06-29 16:48 AEST
Nmap scan report for 192.168.0.211
Host is up (0.0055s latency).
Not shown: 996 closed tcp ports (conn-refused)
PORT    STATE SERVICE
21/tcp  open  ftp
22/tcp  open  ssh
139/tcp open  netbios-ssn
445/tcp open  microsoft-ds

Nmap done: 1 IP address (1 host up) scanned in 1.26 seconds
sumeetsingh@Sumeets-Air ~ % 
```

FIND MAC - USING IP
```bash
sumeetsingh@Sumeets-Air ~ % arp 192.168.0.211
retropie.modem (192.168.0.211) at b8:27:eb:ba:19:85 on en0 ifscope [ethernet]
```

FIND MAC - FROM LOCALHOST
```bash
sumeetsingh@Sumeets-Air ~ % arp -a
? (169.254.169.254) at (incomplete) on en0 [ethernet]
? (192.168.0.0) at ff:ff:ff:ff:ff:ff on en0 ifscope [ethernet]
mymodem.modem (192.168.0.1) at a4:91:b1:c9:dc:c on en0 ifscope [ethernet]
? (192.168.0.2) at (incomplete) on en0 ifscope [ethernet]
? (192.168.0.11) at (incomplete) on en0 ifscope [ethernet]
lifx-color-668f14.modem (192.168.0.14) at d0:73:d5:66:8f:15 on en0 ifscope [ethernet]
? (192.168.0.18) at 1c:f2:9a:5a:36:3 on en0 ifscope [ethernet]
? (192.168.0.20) at 7c:b3:7b:6e:c1:fd on en0 ifscope [ethernet]
? (192.168.0.21) at (incomplete) on en0 ifscope [ethernet]
google-nest-mini-3.modem (192.168.0.23) at f8:f:f9:97:a3:c4 on en0 ifscope [ethernet]
google-nest-mini.modem (192.168.0.63) at d4:f5:47:41:be:5c on en0 ifscope [ethernet]
sumeets-air-2.modem (192.168.0.110) at 14:7d:da:27:c7:85 on en0 ifscope [ethernet]
sumeets-pc.modem (192.168.0.115) at 14:18:c3:9e:3c:d9 on en0 ifscope [ethernet]
lifx-color-66967c.modem (192.168.0.116) at d0:73:d5:66:96:7d on en0 ifscope [ethernet]
espressif.modem (192.168.0.155) at 94:3c:c6:da:4:cc on en0 ifscope [ethernet]
? (192.168.0.187) at e0:9f:2a:e6:60:50 on en0 ifscope [ethernet]
retropie.modem (192.168.0.211) at b8:27:eb:ba:19:85 on en0 ifscope [ethernet]
```


___________________________________________________________________________

                            COMMON SCRIPTS
___________________________________________________________________________

CRON JOB 1 - On low disk usage or high CPU/MEMORY usage alert
```bash

```

CRON JOB 2 - Restart critical services
```bash

```

CRON JOB 3 - Force change old passwords
```bash

```

CRON JOB 4 - Scheduled shutdown
```bash

```