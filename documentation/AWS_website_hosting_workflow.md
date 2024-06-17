___________________________________________________________________________

                    CREATE IAM ROLE FOR WEBSITE UPLOADING
___________________________________________________________________________


1. Create IAM role - In AWS IAM for your region e.g. Sydney create a new IAM role user
https://us-east-1.console.aws.amazon.com/iam/home?region=us-east-1#/users/
attach permissione e.g. the minimum policies needed so that a contractor could upload
a React website and give all backend permissions to a DB are below;
AmazonAPIGatewayAdministrator
AmazonRoute53FullAccess
AmazonS3FullAccess
AWSCertificateManagerFullAccess
AWSCloudFormationFullAccess
AWSLambda_FullAccess
CloudFrontFullAccess

2. Generate a secret key pair



___________________________________________________________________________

                            SETUP DOMAIN AND BUCKET
___________________________________________________________________________

1. In AWS Route 53 by a domain name e.g. agnisamooh.com

2. In AWS Certificate Manager create a new SSL certificate and assign it to the website
e.g, www.agnisamooh.com

2. In your region, click on aws service "cloudfront" e.g.
https://us-east-1.console.aws.amazon.com/cloudfront/v4/home?region=us-east-1#/distributions

create a new distribution and add the websites names;

Alternate domain names
agnisamooh.com
www.agnisamooh.com

3. Under custom SSL certificate choose the cert from AWS certificate manager
Custom SSL certificate
agnisamooh.com 

5. In Route53 point your CNAME to your cloudfront distribution with default values
e.g.
Record name
www.agnisamooh.com
Record type
CNAME
Value
d3ju41dm7641hd.cloudfront.net
Alias
No
TTL (seconds)
300
Routing policy
Simple

6. Create a S3 static hosting butcket. You can use a similar name to your website
e.g. S3 bucket name "agnisamooh.com"
with values
Static website hosting: Enabled
Hosting type: Bucket hosting
Block all public access: Off

___________________________________________________________________________

                        UPLOADING WEBSITE
___________________________________________________________________________

Using CI/CD - to upload React website to S3 static bucket

Assuming you have already created a Repo if not follow ```./git_commands.md```
Then setup website hosting following documentation ```./AWS_website_hosting_workflow.md```
Then add secret key pair to Github repo following guide ```github_workflows.md```

1. Create file: .github\workflows\actions.yml in your repo and add data below then push repo to upload
and test website access

```bash
name: actions
run-name: ${{ github.actor }} Deploy to S3 bucket

on: [push]

jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout repository
        uses: actions/checkout@v2
      
      - name: Sync to S3
        uses: jakejarvis/s3-sync-action@v0.5.1
        with:
          args: --delete
        env:
          AWS_S3_BUCKET: agnisamooh.com
          AWS_ACCESS_KEY_ID: ${{ secrets.AWS_ACCESS_KEY_ID }}
          AWS_SECRET_ACCESS_KEY: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          AWS_REGION: us-east-1
          SOURCE_DIR: './build/'
```


___________________________________________________________________________

                        LAMbDA API's FOR GET/POST
___________________________________________________________________________

see ```AWS_Lambda_API_workflow.md```