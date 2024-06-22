
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
2. Click "Create database "- mysql - set password - use security group with settings
Incomming
Port 22 SSH open for incomming
Outgoing

______________________________________________________________________________________________

                            CONNECT TO DATABASE - CLI
______________________________________________________________________________________________

LOCAL DB AS ROOT
```bash
mysql -u root
```

LOCAL DB AS USER
```bash
mysql -u admin -p
```

REMOTE DB - specify url of DB in -h parameter
```bash
mysql -h agnisamoohmysql.cv43d5o2h5wi.ap-southeast-2.rds.amazonaws.com -u admin -p
```

______________________________________________________________________________________________

                      SETUP ADMIN, DATABASE, TABLE, RECORDS
______________________________________________________________________________________________

```bash
CREATE USER 'admin'@'localhost' IDENTIFIED BY '__REDACTED__';
CREATE DATABASE sumeetsinghdb;
GRANT ALL PRIVILEGES ON sumeetsinghdb.* TO 'admin'@'localhost';
exit
mysql -u admin -p
```
```bash
USE sumeetsinghdb;
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
VALUES ('sum337', 'sumeet.singhji@outlook.com', SHA2('Password!', 256), '', '');
exit
```


______________________________________________________________________________________________

                            CONNECT TO DATABASE - JAVASCRIPT | LAMBDA | API
______________________________________________________________________________________________


LOCAL DB's (e.g, brew/apt/winget mysql installs)

1. Create a login form e.g. LoginForm.js for React below
```javascript
```

2. Create a backend node.js lambda
```javascript
```

3. Test




REMOTE DB's (e.g, AWS RDS)

1. Create a login form e.g. LoginForm.js for React below

```javascript
import React, { useState } from 'react';
import axios from 'axios';
import { useHistory } from 'react-router-dom'; // Import useHistory hook for redirection

function LoginForm() {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [formSubmitted, setFormSubmitted] = useState(false);
  const [showPassword, setShowPassword] = useState(false);
  const [errorMessage, setErrorMessage] = useState('');
  const history = useHistory(); // Initialize useHistory hook

  const togglePasswordVisibility = () => {
    setShowPassword(!showPassword);
  };

  const handleSubmit = async (event) => {
    event.preventDefault();
    try {
      const response = await axios.post('https://ln0w2lsuuc.execute-api.us-east-1.amazonaws.com/$default/login', {
        username,
        password,
      });
      const token = response.data.token; // Retrieve the JWT token from localStorage
      localStorage.setItem('authToken', token); // Store the token in localStorage
      setFormSubmitted(true);
      setErrorMessage('');  // Clear any previous error messages
      // Redirect to Account page
      history.push('/account');
    } catch (error) {
      console.error('Login failed', error);
      setErrorMessage('Login failed. Please check your username and password and try again.');
    }
  };

  return (
    <form onSubmit={handleSubmit}>
      <input
        type="text"
        value={username}
        onChange={(e) => setUsername(e.target.value)}
        placeholder="Username"
      />
      <div>
        <input
          type={showPassword ? 'text' : 'password'}
          value={password}
          onChange={(e) => setPassword(e.target.value)}
          placeholder="Password"
        />
        <button type="button" onClick={togglePasswordVisibility}>
          {showPassword ? 'Hide' : 'Show'}
        </button>
      </div>
      <button type="submit">Login</button>
      {formSubmitted && <p className="success-message">Login successful!</p>}
      {errorMessage && <p className="error-message">{errorMessage}</p>}
    </form>
  );
}

export default LoginForm;

```

2. Create a backend node.js lambda with permissions below to hold the DB details
which are hidden to clients. Remember to click "file save" and "deploy"
```javascript
const connection = await mysql.createConnection({
    host: 'agnisamoohmysql.cv43d5o2h5wi.ap-southeast-2.rds.amazonaws.com',
    user: 'admin',
    password: '___REDACTED___',
    database: 'agnisamoohdb'
});
```

3. in AWS API create a new API with details below

4. Test to connect from the Lambda online. Click on the function name in AWS Lambda.
Click on Test. Enter the below
{
    username: testuser
    password: Testuser$
}

5. In code tab - in expected results - observe if success


______________________________________________________________________________________________

                            COMMON COMMANDS
______________________________________________________________________________________________

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

16. CHANGE PASSWORD
```bash
SET @password = 'user_password'; -- Define the new password
UPDATE users SET password = @password WHERE username = 'sum337';
```

17. LOG OFF
```bash
exit
```