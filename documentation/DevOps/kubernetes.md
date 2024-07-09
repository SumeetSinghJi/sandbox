
___________________________________________________________________________

                            WHAT IS KUBERNETES?
___________________________________________________________________________

2024 ITSM tool comparisons

Ansible (baked with RHEL): Orchestrates tasks and configurations across non cloud devices.
Chef: Same as Ansible but cloud included, requires master control server to monitor activity of 
agents installed on nodes. Nodes require Ruby installed to host agent.
Puppet: Same as Chef
SaltStack: Same as Chef, but requires python instead of ruby
Terraform: Infrastructure provisioning tool only.
* Cloudformation: Similar to Terraform but AWS only.
Kubernetes: Provides above capabilities but for Dockers
* ECS/Fargate: Same as Kubernetes but AWS only.

In Summary if you were to pick 3 ITSM tools only to be vendor agnostic choose;
SaltStack, Terraform and Kubernetes