
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

                            EXAMPLE SETUP
___________________________________________________________________________

We will be setting up a home automation and monitoring website with
Saltstack raspberry pi environment

IP | Device | Location | Setup guide

192.168.0.211 
Raspberry Pi 3B - 
Garage Arcade Machine (minion) - setup with ```../Operating Systems/retropie_setup.md```

192.168.0.210
Raspberry Pi 3B - 
Garage Plex Server - setup with ```../Operating Systems/retropie_setup.md```

192.168.0.209
Raspberry Pi 3B
Bedroom monitoring webserver - setup with ```../Programming/react_webserver.md``` 

192.168.0.208
Raspberry Pi 3B
Bedroom Saltstack control node - setup with below guide


INSTALL SALTSTACK
On 192.168.0.208 run the below
```bash

```







