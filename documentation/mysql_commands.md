
___________________________________________________________________________

                            CREATE DATABASE
___________________________________________________________________________


1. CREATE MYSQL DATABASE - THROUGH AWS RDS
https://ap-southeast-2.console.aws.amazon.com/rds/home?region=ap-southeast-2


___________________________________________________________________________

                            REMOTE CONNECTION
___________________________________________________________________________


1. CONNECT THROUGH CLI (AWS RDS)
```bash
mysql -h agnisamoohmysql.cv43d5o2h5wi.ap-southeast-2.rds.amazonaws.com -u admin -p
```


2. CONNECT THROUGH JAVASCRIPT (DO NOT LEAVE PUBLICALLY FOR TESTING ONLY)
```javascript
const connection = await mysql.createConnection({
    host: 'agnisamoohmysql.cv43d5o2h5wi.ap-southeast-2.rds.amazonaws.com',
    user: 'admin',
    password: '___REDACTED___',
    database: 'agnisamoohdb'
});
```


___________________________________________________________________________

                            MySQL COMMANDS
___________________________________________________________________________

LOGIN
1A. LOGIN AWS RDS:
```bash
mysql -h agnisamoohmysql.cv43d5o2h5wi.ap-southeast-2.rds.amazonaws.com -u admin -p
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

5 VIEW ALL DATABASES
```bash
mysql> show databases;
+---------------------+
| Database            |
+---------------------+
| agnisamoohdb |
| information_schema  |
| mysql               |
| performance_schema  |
| sys                 |
+---------------------+
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
MODIFY order_history INT NOT NULL DEFAULT 0;
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
INSERT INTO users (username, email) VALUES ('sum337', 'kurta.kursi@gmail.com');
```

16. CHANGE PASSWORD
```bash
SET @password = 'user_password'; -- Define the new password
UPDATE users SET password = @password WHERE username = 'sum337';
```

17. LOG OFF
```bash
exit
```