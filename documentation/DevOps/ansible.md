
___________________________________________________________________________

                            WHAT IS ANSIBLE
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

                                ANSIBLE COMMANDS
___________________________________________________________________________


PREREQUISITE
On Linux nodes
1. Install linux nodes, setup SSH and enable firewall
```bash
sudo apt install ufw
sudo ufw enable
sudo ufw allow ssh
sudo ufw status
```
On Windows nodes
1. Enable WinRM service
2. Enable WinRM ports HTTP/5985 and HTTPS/5986
3. Create service account with admin privilges


SETUP CONTROL NODE
```bash
sudo apt install ansible # linux
sudo yum install epel-release # CentOS/RHEL
sudo yum install ansible # CentOS/RHEL
brew install ansible # MacOS
```

SSH KEYGEN
```bash
ssh-keygen # generate a SSH KEY
ssh-copy-id pi@retropie # SSH copy key to every node to manage to bypass passwords 
```

CREATE INVENTORY
```bash
nano /etc/ansible/hosts # Add the nodes to manage to file
[homeautomation]
retropie # arcade machine in garage
```

CREATE PLAYBOOK
```yaml
---
# example below will setup FTP on all linux nodes
- name: Ensure FTP is enabled
  hosts: homeautomation
  become: yes
  tasks:
    - name: Install vsftpd
      apt:
        name: vsftpd
        state: present

    - name: Configure vsftpd
      lineinfile:
        path: /etc/vsftpd.conf
        regexp: "{{ item.regexp }}"
        line: "{{ item.line }}"
      loop:
        - { regexp: '^#?local_enable=', line: 'local_enable=YES' }
        - { regexp: '^#?write_enable=', line: 'write_enable=YES' }

    - name: Ensure vsftpd service is started and enabled
      systemd:
        name: vsftpd
        state: started
        enabled: yes

    - name: Check if port 21 is open
      shell: netstat -tuln | grep ":21 "
      register: ftp_port_check
      ignore_errors: yes

    - name: Display port check result
      debug:
        msg: "{{ ftp_port_check.stdout }}"
```

RUN PLAYBOOK
```bash
ansible-playbook -i inventory site.yml
```
