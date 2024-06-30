___________________________________________________________________________

                            REQUIREMENTS
___________________________________________________________________________

The commands below target the Debian family e.g. Debian, Ubuntu, RaspberryPi
however they can be modified with a quick confirmation with chatGPT to suit
other OS.


___________________________________________________________________________

                            REMOTE CONNECT
___________________________________________________________________________

SSH
e.g. by remoting into raspberry pi with default u: pi p: rasbperry
```bash
ssh pi@192.168.0.211
pi@retropi:~ enter password $ raspberry
```

___________________________________________________________________________

                            FIRST TIME SETUP
___________________________________________________________________________


OPTIONAL - Zsh shell only - enable inline comments with setopt
```bash
testusr@ubuntu Documents % setopt interactive_comments
testusr@ubuntu Documents % echo test # test
test
```

1. ADMINS
```bash
su
usermod -aG sudo vboxuser # or wheel group
cat /etc/sudoers
exit
sudo reboot # necessary to reset admin cache
```

2. UPDATE
```bash
sudo apt update
sudo apt upgrade -y
sudo apt dist-upgrade -y
sudo reboot
```
or
```bash
pacman -Syu
```

3. SSH
```bash
sudo apt install openssh-server -y # for incomming SSH
```

4. HARDEN
```bash
sudo apt install ufw
sudo ufw enable
sudo ufw allow ssh
sudo ufw status
```

5. CLEANUP
```bash
sudo snap remove firefox
```

___________________________________________________________________________

                        SHELL STARTUP SCRIPT
___________________________________________________________________________

Your startup scripts, environmental variables, alias and more are documented
in your shell script located under /home/username/ hidden found with "ls -la"
They need to be added there and the shell restarted for the change to take place.
There are 3 or more shell's usually e.g, ~/.zshrc, ~/.bash or ~/.bash_profile.
edit 1 to include the envionmental variable as per below steps, and remove any outdated version
form the other shell scripts
for MacOS add the path only to: ~/.zshrc


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

                        DEVOPS - C++
___________________________________________________________________________

1. Generic dev
```bash
sudo apt install lolcat, git, flatpak
```

2. For C++ dev
```bash
sudo apt install -y build-essential g++ libboost-all-dev libcurl4-gnutls-dev 
libzip-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev 
zlib1g-dev googletest libgtest-dev yasm
```



___________________________________________________________________________

                    COMMON COMMANDS
___________________________________________________________________________

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
Zsh shell only - enable inline comments with setopt
```bash
testusr@ubuntu Documents % setopt interactive_comments
testusr@ubuntu Documents % echo test # test
test
```
1) in shell script use #
```bash
cd c:\users\sumeetsingh\Documents #windows
```
2) in CLI use line break ; followed by comment next line
```bash
cd c:\users\sumeetsingh\Documents ; #windows
```

SEARCH
```bash
find /usr -iname "*xxx*"
ls | grep xxx
```

SEARCH PACKAGE MANAGER
```bash
pacman -Ss xxxxx
sudo apt search xxxx
sudo apt list --installed xxxxx
```

SEARCH SERVICES - ALL 3 METHODS
```bash
# 1 - through apt
apt list --installed
# 2 - through system services
systemctl list-unit-files
# 3 through manual clone/make/install etc., the binary will be put in /bin and usually in environmental variable
ls /usr/bin 
emulationstation
pi@retropi:~ $ emulationstation # to then start it
```

FIND BIN ENVIRONMENTAL VARIABLE
```bash
sumeetsingh@Sumeets-Air-2 which ruby
/usr/bin/ruby
```
or
```bash
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

DISK FREE/USAGE
```bash
df -h # top level root only
du -h -d 1
```

COPY FILES
```bash
# use -i for confirmation before overwriting
cp "/media/usb1/Silent Hill" /home/pi/RetroPie/roms/psx/ # COPY 1 FILE
cp /media/usb1/* /home/pi/RetroPie/roms/psx/ # COPY ALL FILES
cp -i /media/usb1/* /home/pi/RetroPie/roms/psx/ # COPY ALL FILES + ASK BEFORE OVERWRITING
rm -r "/home/pi/RetroPie/roms/psx/Heart of Darkness (Disc 1)" # IF FAILURE THEN REMOVE TARGET FILE THEN COPY AGAIN
```

MOVE FILES
```bash
# use -i for confirmation before overwriting
mv "/media/usb1/Silent Hill" /home/pi/RetroPie/roms/psx/ # MOVE 1 FILE
mv /media/usb1/* /home/pi/RetroPie/roms/psx/ # MOVE ALL FILES
mv -i /media/usb1/* /home/pi/RetroPie/roms/psx/ # MOVE ALL FILES + ASK BEFORE OVERWRITING
rm -r "/home/pi/RetroPie/roms/psx/Heart of Darkness (Disc 1)" # IF FAILURE THEN REMOVE TARGET FILE THEN COPY AGAIN
```

RENAME
```bash
mv -r /home/me/oldName /home/me/newName  # just use move with recurse to same location
```

RESOLUTION CHANGE
```bash
# If os doesn't fit inside the window e.g. a Retropi in an arcade cabinet
# has the bottom screen e.g. the text CLI prompt part cut off, then
# adjust the overlay
sudo nano /boot/config.txt
# uncomment the below and the higher the number the more it moves in so
overscan_left=16 # padding 16 from left
overscan_bottom=60 # padding from the bottom
# if using nano
# CTRL - X
# Y
# PRESS ENTER
# done. If error, then close file and run with sudo
sudo reboot now # then view screen, test and adjust accordingly
```


___________________________________________________________________________

                    NETWORKING COMMANDS
___________________________________________________________________________

OPEN PORTS
find all open ports
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

