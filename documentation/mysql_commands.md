
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

                      SETUP ADMIN, DATABASE, TABLE, RECORDS
______________________________________________________________________________________________

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
-- for demonstration purposes we will use password: Password1!
VALUES ('sum337', 'sumeet.singhji@outlook.com', SHA2('Password1!', 256), '', '');
```


______________________________________________________________________________________________

                          CONNECT TO DATABASE - JAVASCRIPT/REACT
______________________________________________________________________________________________

CREATE REACT LOGIN FORM COMPONENT

1. Create a login form for react named: LoginForm.js
If using a localhost use post url: http://localhost:5000/login
if using a remote url API it there e.g. AWS RDS: https://7ok9pqxlg4.execute-api.us-east-1.amazonaws.com/PROD/login
```javascript
1. Create a login form e.g. LoginForm.js for React below
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
      const response = await axios.post('http://localhost:5000/login', {
        username,
        password,
      });
      const token = response.data.token; // Retrieve the JWT token from localStorage
      localStorage.setItem('authToken', token); // Store the token in localStorage
      setFormSubmitted(true);
      setErrorMessage('');  // Clear any previous error messages
      history.push('/account'); // Redirect to Account page
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

2. Create a login page and import the LoginForm.js
see ```react_commands.md```

3. OPTIONAL - Create a account page to redirect to
see ```react_commands.md```

LOCALHOST BACKEND FILE CREATE

1. Create a backend node.js named: src/components/backend/Server.js
```javascript
const express = require('express');
const bodyParser = require('body-parser');
const mysql = require('mysql2/promise');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const cors = require('cors');

const app = express();
const port = 5000;

const SECRET_KEY = "___YOUR_SECRET_KEY1!___";

app.use(bodyParser.json());
app.use(cors());

const dbConfig = {
  host: '127.0.0.1',
  user: 'admin',
  password: 'Password1!',
  database: 'agnisamoohdb',
};

app.post('/login', async (req, res) => {
  const { username, password } = req.body;

  try {
    const connection = await mysql.createConnection(dbConfig);
    const [rows] = await connection.execute('SELECT * FROM users WHERE username = ?', [username]);

    if (rows.length === 0) {
      return res.status(401).json({ error: 'Invalid credentials' });
    }

    const user = rows[0];
    const passwordMatch = await bcrypt.compare(password, user.password);

    if (!passwordMatch) {
      return res.status(401).json({ error: 'Invalid credentials' });
    }

    const token = jwt.sign({ username: user.username, userId: user.id }, SECRET_KEY, { expiresIn: '1h' });

    return res.status(200).json({ token });
  } catch (error) {
    console.error('Login error:', error);
    return res.status(500).json({ error: 'Internal server error' });
  }
});

app.listen(port, () => {
  console.log(`Server running on http://localhost:${port}`);
});
```

2. Install backend dependencies in your react project
```bash
cd src
npm install express mysql2 bcryptjs jsonwebtoken body-parser cors
```

3. Start the server
```bash
cd components/backend
node server.js
```

REMOTE BACKEND FILE CREATE

1. Create a backend node.js lambda with permissions below to hold the DB details
which are hidden to clients. Remember to click "file save" and "deploy"
```bash
1. Go to lambda functions - create new function - function name: agnisamooh-login-lambda-post
2. Runtime node.js 20.x
3. Create function
4. In code source main page add the code below and click - file - save - then click "deploy"
```
url: https://us-east-1.console.aws.amazon.com/lambda/home?region=us-east-1#/functions
```javascript
const jwt = require('jsonwebtoken');
const mysql = require('mysql2/promise');
const bcrypt = require('bcryptjs');

const dbConfig = {
  host: 'agnisamoohmysql.cv43d5o2h5wi.ap-southeast-2.rds.amazonaws.com',
  user: 'admin',
  password: 'Agnisamooh-1!',
  database: 'agnisamoohdb',
};

exports.handler = async (event) => {
  const { username, password } = JSON.parse(event.body);

  const connection = await mysql.createConnection(dbConfig);
  const [rows] = await connection.execute('SELECT * FROM users WHERE username = ?', [username]);

  if (rows.length === 0) {
    return {
      statusCode: 401,
      body: JSON.stringify({ error: 'Invalid credentials' }),
    };
  }

  const user = rows[0];
  
  const passwordMatch = await bcrypt.compare(password, user.password);
  
  if (!passwordMatch) {
    return {
      statusCode: 401,
      body: JSON.stringify({ error: 'Invalid credentials' }),
    };
  }

  const token = jwt.sign({ username: user.username, userId: user.id }, 'YOUR_SECRET_KEY', { expiresIn: '1h' });

  return {
    statusCode: 200,
    body: JSON.stringify({ token }),
  };
};
```

2. in AWS API create a new API with details below
url: https://us-east-1.console.aws.amazon.com/apigateway/main/precreate?region=us-east-1 
```bash
1. In AWS "API Gateway" - click build new HTTP API
2. API Name e.g,: agnisamooh-login-post-api
3. Stage name: PROD
4. Click Create to save the API
5. Go back to API's then click on the API. It will take you to the routes page
6. Click "Create a Route"
7. Route method: POST
8. Route name: /login
9. Click create
10. Click on "integrations" on the left side
11. Click create an attach an integration
12. Integration target "lambda function"
13. In the drop down select the previous created Lambda function
14. Click create
15. Click back on the API in the left navigation bar then make note of the
ARN e.g, https://7ok9pqxlg4.execute-api.us-east-1.amazonaws.com
```

3. Go back to the LoginForm.js and add the API to the response url adding the stage and api path
```javascript
const response = await axios.post('https://7ok9pqxlg4.execute-api.us-east-1.amazonaws.com/PROD/login', {
        username,
        password,
      });
```

TESTING

1. Test by starting the react website and testing the login form page
```bash
cd YOUR_REACT_PROJECT_PATH/src
npm start
1. www.agnisamooh.com/login
2. Fill out login form page with 
username; sum337
password; Password1!
3. You should be redirected to the account page
```

2. If above test is successfull for login remember to log back into mysql and change the
admin password and the users table test user record password. Replace the password placeholder with a new
password
```bash
-- CHANGE THE -h AND PASSWORD
mysql -h 127.0.0.1 -u root -p -e "ALTER USER 'admin'@'localhost' IDENTIFIED BY 'new_password_goes_here'; USE agnisamoohdb; UPDATE users SET password = 'new_password_goes_here' WHERE username = 'sum337';"
```

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
SET @password = 'user_password'; -- Define the new password
UPDATE users SET password = @password WHERE username = 'sum337';
```

17. LOG OFF
```bash
exit
```