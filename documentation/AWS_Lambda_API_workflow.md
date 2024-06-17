___________________________________________________________________________

            LAMBDA - (OPTIONAL) SCHEDULE DATABASE START/STOP
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

              LAMBDA - FETCH API - POST DATABASE LOGIN RECORDS
___________________________________________________________________________





___________________________________________________________________________

              LAMBDA - FETCH API - GET DATABASE LOGIN RECORDS
___________________________________________________________________________