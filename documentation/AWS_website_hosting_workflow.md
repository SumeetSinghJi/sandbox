________________________________________________________

                    UPLOADING WEBSITE
________________________________________________________

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

                            SETUP DOMAIN AND BUCKET
___________________________________________________________________________

1. In AWS Route 53 by a domain name e.g. agnisamooh.com

2. In AWS Certificate Manager

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

7. Upload your website manually or using Ci/Cd e.g. if uploading a react
website follow CICD steps from ```react_commands.md``` you will require
an IAM role setup. You can follow the permissions below.


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

                    LAMBDA - DATABASE SCHEDULED START OR STOPPING
___________________________________________________________________________

Considering you created an RDS Database or similar AWS DB service

1. Create an IAM role with policies (permissions) for accessing resources
e.g. IAM = "Start-RDS-DB-role" and policies are predefined and selected
"RDSFullAccess", "CloudwatchFullAccess"

2. Go to Lambda, create new function, select your programming environment
e.g. node.js OR python (easiest) and attach role above "Start-RDS-DB-role"

3. In function page, under code, type the code. Click "File - Save" then
click "Deploy" (IMPORTANT)

4. Still in code section under "Test" edit code to only be "{}" representing an empty string
as your not sending any data for this test, then click "TEST"

5. You will see results under "Execution Results". Note if you clicked "TEST" from the above
navigation bar, you will get an option to follow the Cloudwatch logs URL. Click on it
and observe the logs for that timestamp period to see results.

OPTIONAL - TRIGGERS

AUTOMATIC SCHEDULING
1. You can set a trigger by clicking on "Add triggers" in AWS Lambda function page's page.
Then click EventBridge Cloudwatch - if you want to set as schedule


___________________________________________________________________________

                    LAMBDA - DATABASE POST LOGIN DATA
___________________________________________________________________________

