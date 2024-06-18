
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
# or
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
nano ~/.zshrc
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

                        DEVOPS
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

DISPLAY
```bash
sudo systemctl status display-manager
```

DISK FREE/USAGE
```bash
df -h # top level root only
du -h -d 1
```
