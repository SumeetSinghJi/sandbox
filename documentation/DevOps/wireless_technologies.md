
___________________________________________________________________________

# WIFI EXTENDERS
___________________________________________________________________________

WiFi Extender modes

Proxy
No static IP addressing possible. Wifi extenders change the MAC address of 
all clients to itself so when you do an arp -a discovery, all clients on 
that extender will be summarised. If static addressing is still required
you will need to exclude IP's from pool in home router, and have the client
manually assign them out.

Universal
Allow static IP addressing
All clients will have the first 3 hexedecimal characters replaced with the Wifi
extenders.

