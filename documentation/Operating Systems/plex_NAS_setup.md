
___________________________________________________________________________

                UNIX* PLEX & NAS SETUP
___________________________________________________________________________

1. INSTALL PLEX
```bash
curl https://downloads.plex.tv/plex-keys/PlexSign.key | sudo apt-key add -
echo deb https://downloads.plex.tv/repo/deb public main | sudo tee /etc/apt/sources.list.d/plexmediaserver.list
sudo apt update
sudo apt install plexmediaserver
```

2. (OPTIONAL) MOUNT STORAGE
```bash
# If using a m.2 hat on a Pi, or the storage is not auto mounted at boot follow below
sudo fdisk -l
sudo mkfs.ext4 /dev/sdX1
sudo mkdir /mnt/nvme
sudo mount /dev/sdX1 /mnt/nvme
```

3. INSTALL SAMBA
```bash
sudo apt install samba
sudo nano /etc/samba/smb.conf
[PlexMedia]
path = /mnt/nvme
browseable = yes
writeable = yes
only guest = no
create mask = 0755
public = yes

sudo smbpasswd -a pi
sudo systemctl restart smbd
```

4. ACCESSING NAS
```bash
On Windows, open File Explorer and type \\<Raspberry_Pi_IP_Address>\PlexMedia in the address bar.
On macOS, use Finder and select Go > Connect to Server, then type smb://<Raspberry_Pi_IP_Address>/PlexMedia.
```

5. CONFIGURE PLEX TO USE NAS
```bash
1. Open the Plex web interface.
2. Go to Settings > Libraries and add the media folders located on your NVMe SSD.
```