
___________________________________________________________________________

                            CHECK OPEN PORTS
___________________________________________________________________________

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




___________________________________________________________________________

                            FIND MAC ADDRESS
___________________________________________________________________________

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

