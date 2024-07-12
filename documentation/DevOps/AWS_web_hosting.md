___________________________________________________________________________

                  SETUP DOMAIN, BUCKET and UPLOAD TEST WEBPAGE
___________________________________________________________________________

1. Buy a domain name in AWS Route 53
URL: https://us-east-1.console.aws.amazon.com/route53/domains/home
```bash
sumeet-singh.com
```

2. Choose a region for your website
URL: https://ap-southeast-2.console.aws.amazon.com/s3/home?region=ap-southeast-2  
```bash
ap-southeast-2
```

3. In AWS Certificate Manager request certificate - Must use us-east-1 (Virginia) ONLY, Cloudfront only uses North America SSL's
URL: https://us-east-1.console.aws.amazon.com/acm/home?region=us-east-1#/certificates/list
```bash
1. Request certificate
2. Amazon issued public SSL certificate
3. Enter FQDN e.g, sumeet-singh.com
Click add another domain name and enter the www version e.g. www.sumeet-singh.com
4. Default DNS validation
5. Default Key Algorithm RSA 2048
6. Go to list certificates and click on the new certificate
7. Click "create records in Route 53" - NOTE: Ensure there are no existing CNAME records in that domain
for existing accounts. If present delete all CNAME records in Route53 before clicking to add these new records
8. Wait until certificates say success/validated/verified
```

4. Create a test page index.html with code below;
```html
<!-- WEBSITE UNDER CONSTRUCTION TEMPLATE -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Under Construction</title>
    <style>

        body {
            background-color: gray;
            font-family: Arial, Helvetica, sans-serif;
            display: flex;
            height: 100vh; /* make the body an single flex box, by assigning it 100% of viewport */
            justify-content: center; /* allign in centre of row */
            align-items: center; /*  allign in centre of column */
        }
        h1 {
            font-size: 30;
            color: white;
        }
    </style>
</head>
<body>
    <h1>Under Construction</h1>
</body>
</html>

```

5. In AWS Service S3 Create a bucket
URL: https://ap-southeast-2.console.aws.amazon.com/s3/home?region=ap-southeast-2
```bash
1. Click Create bucket
2. Add values below
Bucket name = sumeet-singh.com
Block Public access settings for this bucket - Uncheck
Check warning confirmation bucket will be public
In bucket policy enter code below

{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "PublicReadForGetBucketObjects",
            "Effect": "Allow",
            "Principal": "*",
            "Action": "s3:GetObject",
            "Resource": "arn:aws:s3:::sumeet-singh.com/*"
        }
    ]
}
Then click create bucket
3. Click on bucket https://ap-southeast-2.console.aws.amazon.com/s3/buckets/sumeet-singh.com?region=ap-southeast-2&bucketType=general&tab=objects 
4. Under properties scroll down to Static website hosting - click edit - enable
index document index.html
5. Set error page to: index.html
Then click save
6. Under Objects - click upload - add files - select the index.html - then click upload
```

6. In service AWS Cloudfront create a new distribution
URL: https://us-east-1.console.aws.amazon.com/cloudfront 
IMPORTANT: only AWS Certificate's made in us-east-1 can be used
```bash
1. Create distribution
2. In choose origin domain select the new bucket sumeet-singh.com.s3 - then click use website endpoint - then repeat until confirmed
3. Add alternate domain name: sumeet-singh.com, and the www record www.sumeet-singh.com
4. Allowed HTTP methods = The last option GET, HEAD, OPTIONS, PUT, POST, PATCH, DELETE - which will allow API usage
5. For cost saving method select Do not enable AWS WAF
6. In Custom SSL certificate select your cert e.g, sumeet-singh.com 
7. Click create distribution
8. Make note of the Distrbution domain name e.g, https://d3hvilctvbbd7e.cloudfront.net
9. Click on "error pages" tab - click "create custom error message" - set to 404 - set custom error - seto to 404 - set to /index.html
```

8. In Route53 point your CNAME to your cloudfront distribution with default values
e.g.
```bash
Create the first record 
Record name: www
Record type: CNAME
Value: d3hvilctvbbd7e.cloudfront.net
Alias: No
TTL (seconds): 300
Routing policy: Simple

Now create another record
1. click create record
2. Click record wizard - Simple routing
3. Choose select a endpoint - cloudfront distribution
4. In distribution select the previous cloudfront distribution
5. Save record
```
You should have the following records
Recrord - URL - value
A - sumeet.singh.com - d3hvilctvbbd7e.cloudfront.net
CNAME - www.sumeet-singh.com - d3hvilctvbbd7e.cloudfront.net

10. Now test website from both URL's
sumeet-singh.com
www.sumeet-singh.com
If any failures diagnose with mxtoolbox.com by searching the relevant error domain and fixing errors


___________________________________________________________________________

                    CREATE IAM ROLE FOR WEBSITE UPLOADING
___________________________________________________________________________


1. Create IAM role - In AWS IAM for your region e.g. Sydney create a new IAM role user
https://us-east-1.console.aws.amazon.com/iam/home?region=us-east-1#/users/
attach permissione e.g. the minimum policies needed so that a contractor could upload
a React website and give all backend permissions to a DB are below;
```bash
AmazonAPIGatewayAdministrator
AmazonRoute53FullAccess
AmazonS3FullAccess
AWSCertificateManagerFullAccess
AWSCloudFormationFullAccess
AWSLambda_FullAccess
CloudFrontFullAccess
```

2. Generate a secret key pair.

3. If using version control/GitHub/CI/CD you may want to add
the 2 keys as secret repository variables in order to push the code using CI/CD directly
to the bucket.

Go here: https://github.com/SumeetSinghJi/sumeet-singh.com/settings/secrets/actions

a. Click "New repository secret"
b. make key with name: AWS_ACCESS_KEY_ID and value: the_keys_value
c. save.
d. Click "New repository secret" again
e. make another key with name: AWS_SECRET_ACCESS_KEY and value: the_keys_value


___________________________________________________________________________

                        UPLOADING REACT WEBSITE
___________________________________________________________________________


Upload manually by uploading output of ```npm run build``` to S3 bucket
or use CI/CD e.g. with Github actions in ```github_actions_commands.md```