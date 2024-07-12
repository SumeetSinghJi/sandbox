
___________________________________________________________________________

                            WHAT IS SALTSTACK
___________________________________________________________________________

2024 ITSM tool comparisons

Ansible: Orchestrates tasks and configurations across non cloud devices.
Chef: Same as Ansible, requires master control server to monitor activity of 
agents installed on nodes. Nodes require Ruby installed to host agent.
Puppet: Same as Chef
SaltStack: Same as Chef, but requires python instead of ruby
Terraform: Infrastructure provisioning tool only.
Cloudformation: Similar to Terraform but AWS cloud only
Kubernetes: Provides above capabilities but for Dockers
ECS/Fargate: Same as Kubernetes but AWS cloud only.

In Summary if you were to pick 3 ITSM tools only to be agnostic choose;
SaltStack, Terraform and Kubernetes






___________________________________________________________________________

                            DOCKER SETUP
___________________________________________________________________________


1. Install SaltStack Minion (Agent software) on desired node
```bash
# Example install on Raspberry Pi 3B+ running Retropi located in garage - 192.168.0.211
curl -L https://bootstrap.saltproject.io -o install_salt.sh
sudo sh install_salt.sh -P -M
sudo nano /etc/salt/minion
master: _____SALTMASTER_IP_GOES_HERE_____
sudo systemctl restart salt-minion
```

2. CREATE FILE docker-compose.yml
```yaml
version: '3'

services:
  saltmaster:
    image: saltstack/salt-master:latest
    container_name: saltmaster
    ports:
      - "4505:4505"
      - "4506:4506"
    volumes:
      - /path/to/salt/config:/etc/salt
      - /path/to/salt/pki:/etc/salt/pki
    restart: unless-stopped
```

3. START DOCKER
```bash
docker-compose up -d
```

4. ACCEPT SALT MINION KEY
```bash
sudo salt-key -L  # List keys
sudo salt-key -A  # Accept all pending keys
```

5. TEST CONNECTIVITY FROM MASTER TO MINION
```bash
sudo salt '<minion_id_or_ip>' test.ping  # Check if minion is responding
sudo salt '<minion_id_or_ip>' cmd.run 'ls /home/pi'  # Example command
```


