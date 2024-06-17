________________________________________________________

                    CREATING REPO SECRETS
________________________________________________________

1. Follow ```AWS_website_hosting_workflow.md``` to setup an IAM role
with policy permissions and generate a key pair

2. In the Github repo create a Repository secrets e.g,
https://github.com/SumeetSinghJi/AgniSamooh/settings/secrets/actions/new

called ```AWS_ACCESS_KEY_ID``` with value of AWS key

then create another Repository secrets called ```AWS_SECRET_ACCESS_KEY```
with the secret key ID value