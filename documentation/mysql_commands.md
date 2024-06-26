
______________________________________________________________________________________________

                                CREATE DATABASE
______________________________________________________________________________________________

MacOS
OPTIONAL - check brew already installed and if so start
1. brew services
2. brew services start mysql
IF BREW NOT INSTALLED
1. brew install mysql
2. brew services start mysql
OPTIONAL - to find the database directory on host
1. mysql -u root -e "SHOW VARIABLES LIKE 'datadir';"\n


AWS RDS
1. Go to AWS RDS REGION
https://ap-southeast-2.console.aws.amazon.com/rds/home?region=ap-southeast-2
2. Click "Create database "- mysql - set any password - create default security group which
will auto create with below default settings
Incomming
IPv4	MYSQL/Aurora	TCP	3306
Outgoing
everything/default/*
______________________________________________________________________________________________

                            CONNECT TO DATABASE - CLI
______________________________________________________________________________________________

OPTIONAL - Find DB running port MacOS/Linux
Result is usually default 3306
```bash
sumeetsingh@Sumeets-Air sandbox % lsof -iTCP -sTCP:LISTEN -P | grep mysql 

mysqld    37199 sumeetsingh   18u  IPv4 0x4854526e13fbf6b6      0t0  TCP localhost:33060 (LISTEN)
mysqld    37199 sumeetsingh   20u  IPv4 0x5d9b0a6e5c20275a      0t0  TCP localhost:3306 (LISTEN)
```

LOCAL DB AS ROOT
```bash
mysql -u root -p
```

LOCAL DB AS USER
```bash
mysql -u admin -p
```

REMOTE DB - specify url of DB in -h parameter
```bash
-- you can use -h localhost OR 127.0.0.1
mysql -h agnisamoohmysql.cv43d5o2h5wi.ap-southeast-2.rds.amazonaws.com -u admin -p
```

______________________________________________________________________________________________

                                    HASH PASSWORD
______________________________________________________________________________________________

To securely store a user password into a MySQL DB, we can use insecure SHA, or use bcrypt to
hash the password securely with an algorithm

1. Requires node.js installed see ```node_commands.md``` for more details on how to install
libs bcrypt

2. Create file anywhere, ideally in /src/components/backend/HashPassword.js
```javascript
// HashPassword.js
const bcrypt = require('bcryptjs');

const password = 'Password1!'; // Change this to any value
const saltRounds = 10;

bcrypt.hash(password, saltRounds, (err, hash) => {
  if (err) {
    console.error('Error hashing password:', err);
  } else {
    console.log('Hashed password:', hash);
  }
});
```

3. Run code above
```bash
cd project-directory/src/components/backend
node HashPassword.js
```

4. You will get an output similar to below
```bash
sumeetsingh@Sumeets-Air backend % node HashPassword.js
Hashed password: $2a$10$9JsnQAMsal.4iMhX.CnZXuy9aCILeipHjLt8MGf5h.JJ64KSg.uOy
```

______________________________________________________________________________________________

                      SETUP ADMIN, DATABASE, TABLE, RECORDS
______________________________________________________________________________________________

1. Run the below code in MySQL once connected through CLI, remember to change
the users password to a Hash password e.g. from step earlier to hash a password

If the users password is already set from a different password encryption method
use AlTER user following steps in COMMON COMMANDS to change it to new hashed password

e.g, update users set password = '$2a$10$9JsnQAMsal.4iMhX.CnZXuy9aCILeipHjLt8MGf5h.JJ64KSg.uOy' where username = 'sum337';

```bash
CREATE USER 'admin'@'localhost' IDENTIFIED BY 'Password1!';
CREATE DATABASE agnisamoohdb;
GRANT ALL PRIVILEGES ON agnisamoohdb.* TO 'admin'@'localhost';
USE agnisamoohdb;
CREATE TABLE users (
    userID INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(20) NOT NULL,
    email VARCHAR(50) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    onMailingList TINYINT(1) NOT NULL DEFAULT 0,
    pending_orders INT NOT NULL DEFAULT 0,
    order_history INT NOT NULL DEFAULT 0,
    open_tickets INT NOT NULL DEFAULT 0,
    closed_tickets INT NOT NULL DEFAULT 0,
    subscriptions VARCHAR(1000) NOT NULL,
    notes VARCHAR(1000) NOT NULL
);
INSERT INTO users (username, email, password, subscriptions, notes)
VALUES ('sum337', 'sumeet.singhji@outlook.com', '$2a$10$9JsnQAMsal.4iMhX.CnZXuy9aCILeipHjLt8MGf5h.JJ64KSg.uOy', '', '');
```


______________________________________________________________________________________________

                          CONNECT TO DATABASE - JAVASCRIPT/REACT
______________________________________________________________________________________________

See ```react_commands.md``` for details on how to connect with Javascript/React


______________________________________________________________________________________________

                            COMMON COMMANDS
______________________________________________________________________________________________

1. COMMENTS
```bash
-- this is first comment
select * from users; -- this is second comment
```

2. FIND ALL MYSQL USERS (Must be logged in as root)
```bash
SELECT user, host FROM mysql.user;
```

3. CREATE A USER
```bash
CREATE USER 'user'@'localhost' IDENTIFIED BY 'password';
```

4. CHANGE PASSWORD FOR ANY USER
```bash
ALTER USER 'user'@'localhost' IDENTIFIED BY 'new_password_goes_here';
```

5. VIEW ALL DATABASES
```bash
mysql> show databases;
+---------------------+
| Database            |
+---------------------+
| agnisamoohdb        |
| information_schema  |
| mysql               |
| performance_schema  |
| sys                 |
+---------------------+
```

5.5 DELETE DATABASE
```bash
DROP DATABASE xxx
```

6. CREATE DATABASE
```bash
CREATE DATABASE agnisamoohdb;
```

7. GRANT DATABASE ACCESS TO USER
```bash
GRANT ALL PRIVILEGES ON agnisamoohdb.* TO 'user'@'localhost';
```

8. ACCESS DATABASE
```bash
USE agnisamoohdb;
```

9. SHOW TABLES
```bash
mysql> show tables;
+------------------------+
| Tables_in_agnisamoohdb |
+------------------------+
| users                  |
+------------------------+
```

10. CREATE TABLE
```bash
# RULES for one time users like records, except the private key always try to set NOT NULL, so you cannot have null entries
# then for ints and booleans set DEFAULT 0;
CREATE TABLE users (
    userID INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(20) NOT NULL,
    email VARCHAR(50) UNIQUE NOT NULL,
    password VARCHAR(20) NOT NULL
);
```

11. SHOW COLUMNS
```bash
DESCRIBE users;
+----------+-------------+------+-----+---------+----------------+
| Field    | Type        | Null | Key | Default | Extra          |
+----------+-------------+------+-----+---------+----------------+
| userID   | int         | NO   | PRI | NULL    | auto_increment |
| username | varchar(20) | NO   |     | NULL    |                |
| email    | varchar(50) | NO   |     | NULL    |                |
| password | varchar(20) | NO   |     | NULL    |                |
+----------+-------------+------+-----+---------+----------------+
4 rows in set (0.12 sec)
```

12. QUERY TABLE
```bash
SELECT * FROM users;
```

13. CREATE NEW COLUMN
```bash
ALTER TABLE users
ADD COLUMN onMailingList BOOLEAN NOT NULL DEFAULT 0,
ADD COLUMN pending_orders INT NOT NULL DEFAULT 0,
ADD COLUMN order_history INT NOT NULL DEFAULT 0,
ADD COLUMN open_tickets INT NOT NULL DEFAULT 0,
ADD COLUMN closed_tickets INT NOT NULL DEFAULT 0,
ADD COLUMN games TEXT NOT NULL,
ADD COLUMN bubbleup_game_statistics TEXT NOT NULL;
```

15. MODIFY TABLE
```bash
ALTER TABLE users
MODIFY order_history TEXT NOT NULL;
```
```bash
+--------------------------+-------------+------+-----+---------+----------------+
| Field                    | Type        | Null | Key | Default | Extra          |
+--------------------------+-------------+------+-----+---------+----------------+
| userID                   | int         | NO   | PRI | NULL    | auto_increment |
| username                 | varchar(20) | NO   |     |         |                |
| email                    | varchar(50) | NO   |     |         |                |
| password                 | varchar(20) | NO   |     |         |                |
| onMailingList            | tinyint(1)  | NO   |     | 0       |                |
| pending_orders           | int         | NO   |     | 0       |                |
| order_history            | text        | NO   |     | NULL    |                |
| open_tickets             | int         | NO   |     | 0       |                |
| closed_tickets           | int         | NO   |     | 0       |                |
| games                    | text        | NO   |     | NULL    |                |
| bubbleup_game_statistics | text        | NO   |     | NULL    |                |
+--------------------------+-------------+------+-----+---------+----------------+
```

15. CREATE NEW USER
```bash
INSERT INTO users (username, email, password, subscriptions, notes) 
VALUES ('sum337', 'sumeet.singhji@outlook.com', SHA2('Password!', 256), '', '');
```

16. CHANGE USER RECORD PASSWORD
```bash
UPDATE users SET password = 'Password1!' WHERE username = 'sum337';
```

17. LOG OFF
```bash
exit
```