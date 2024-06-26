___________________________________________________________________________

                          REACT VS JAVASCRIPT
___________________________________________________________________________

The example below shows the differences between vanilla javascript vs react.

Basic Javascript requires getting elements (DOM Manipulation), attaching 
event listeners (Event Handling) and hardcoding the html tags (non reuseable), 
whereas React abstracts the former in reusable components.

React uses "state" by assigning variables/functions a state. That dynamically
update the front end based on actions e.g. the button clicks on return html code.

JAVASCRIPT
```html
<body>
    <div class="counter">
        <h2>Counter Example</h2>
        <!-- usage -->
        <p>Count: <span id="count">0</span></p>
        <button class="btn" id="incrementBtn">Increment</button>
        <button class="btn" id="decrementBtn">Decrement</button>
    </div>

    <script>
        let count = 0;

        const increment = () => {
            count++;
            updateUI();
        };

        const decrement = () => {
            count--;
            updateUI();
        };

        const updateUI = () => {
            const countElement = document.getElementById('count');
            countElement.textContent = count;
        };

        // Event listeners for buttons
        document.getElementById('incrementBtn').addEventListener('click', increment);
        document.getElementById('decrementBtn').addEventListener('click', decrement);
    </script>
</body>
</html>
```

REACT
```javascript
// src/components/Counter.js
import React, { useState } from 'react';

const Counter = () => {
    const [count, setCount] = useState(0);

    const increment = () => {
        setCount(count + 1);
    };

    const decrement = () => {
        setCount(count - 1);
    };

    return (
        <div>
            <button onClick={increment}>Increment</button>
            <button onClick={decrement}>Decrement</button>
            <p>Count: {count}</p>
        </div>
    );
};

// usage in src/App.js
import Counter from './components/Counter';

function App() {
    return (
        <div>
          <div class="counter">
            <h1>Counter example</h1>
            <Counter />
          </div>
        </div>
    );
}

export default App;
```

___________________________________________________________________________

                          INSTALLING REACT
___________________________________________________________________________

1. Install node.js
```bash
Windows: winget install Node.js
MacOS: brew install node
Linux: apt install node
```

___________________________________________________________________________

                  OPTIONAL - INSTALL CLONED WEBSITE
___________________________________________________________________________

1. IF CLONING REACT FOR FIRST TIME
```bash
npm install
```

OPTIONAL - RESET/CLEAR NODE MODULES CACHE IF ERRORS OCCUR DURING INSTALLATION
```bash
npm cache clean --force
```

___________________________________________________________________________

                          CREATE WEBSITE
___________________________________________________________________________

DESCRIPTION
The steps below will create a website with
* Account details form page
* Contact us form page
* Shopping cart form page

REQUIREMENTS
Creating a remote AWS RDS (but local DB commansd also here) 
following guide ```MySQL_commands```

1. Change to parent directory to host website project directory
```bash
cd c:\users\sumeetsingh\Documents ; #windows
cd /Users/sumeetsingh/Documents ; #macos
```

2. Install create-react-app globally. Recommended as it will hold all other libs
```bash
npm install -g create-react-app
```

3. CREATE REACT WEBSITE TEMPLATE
will initialise git, create .gitignore configured to ignore node_modules. Ready to commit
```bash
create-react-app sumeet-singh.com
```

4. MOVE INTO PROJECT
```bash
cd sumeet-singh.com
```

5. INSTALL LIBS IN ./NODE_MODULES
```bash
npm install react-router-dom
```

6. DELETE DEFAULT FILES + REMOVE ENTRIES
```bash
# Delete all unnecessary files
cd public
rm logo192.png logo512.png manifest.json robots.txt

# Delete unnecessary lines in index.html
sed -i "" '12,26d' ./index.html
sed -i "" '17,26d' ./index.html

cd ../src
rm App.js App.test.js index.css logo.svg reportWebVitals.js setupTests.js

# Populate App.js with general boilerplate
touch App.js
echo "function App() {
  return <div className='App'>Hello World</div>;
}
export default App;" >> App.js

# Delete unnecessary lines in index.js
sed -i "" '3d' ./index.js
sed -i "" '4d' ./index.js
sed -i "" '12,15d' ./index.js
```

7. CHANGE TITLE
change the <title> tag in /public/index.html to the websites name e.g. <title>Sumeet Singh</title>

8. CD TO SRC
```bash
cd src
```

9. CREATE ALL FOLDERS
```bash
mkdir assets # for assets e.g. graphics, sounds, images, videos to display on webpage
mkdir assets/graphics
mkdir assets/graphics/logos
mkdir assets/sounds
mkdir assets/videos
mkdir pages # for pages e.g. homepage.js, contactus.js, news.js
mkdir components # for reusable assets e.g. header.js, footer.js
mkdir components/backend # for backend code e.g. SubmtiSignUp.js, SubmitLogin.js
```

10. ADD FAVICON AND LOGO
```bash
cp path_to_your/favicon.ico /public/favicon.ico
cp path_to_your/logo.png /src/assets/graphics/logos/logo.png
```

12. REPLACE DEFAULT CSS /src/App.css
```css
/* 
The example CSS below is for a flex website for more information on how to
use flex read ULTIMATE FLEX GUIDE: https://css-tricks.com/snippets/css/a-guide-to-flexbox/ 

Uses a HTML structure as below
<div className="wrapper">
<header>
<main>
<footer>
</div>
*/
/* Reset and basic styles */
body, html, #root {
  font-family: Arial, sans-serif; /* Fallback font */
  margin: 0;
  padding: 0;
  height: 100%;
  box-sizing: border-box; /* Ensures padding and border are included in total width/height */
}

/* Wrapper for entire layout */
.wrapper {
  display: flex;
  flex-direction: column; /* Stacks header, main content, and footer vertically */
  min-height: 100vh; /* Ensures wrapper spans the full viewport height */
}

/* Header styles */
.header {
  display: flex;
  justify-content: space-between; /* Space between logo and nav links */
  align-items: center; /* Center items vertically */
  padding: 1rem; /* Padding around header content */
  background-color: #f8f9fa; /* Background color for header */
}

.header a {
  text-decoration: none; /* Remove underline from links */
  color: black; /* Set link color */
}

.header a:hover {
  text-decoration: underline; /* Add underline on hover */
}

.header img {
  width: 100px; /* Fixed width for logo */
  height: 100px; /* Fixed height for logo */
}

/* Navigation links styles specific to header */
.header .nav-links {
  display: flex; /* Align links horizontally */
  list-style: none; /* Remove default list styles */
  margin: 0; /* Remove default margin */
  padding: 0; /* Remove default padding */
}

.header .nav-links li {
  margin: 0 1rem; /* Space between each link */
}

.header .nav-links li a {
  text-decoration: none; /* Remove underline from links */
  color: black; /* Set link color */
}

.header .nav-links li a:hover {
  text-decoration: underline; /* Add underline on hover */
}

/* Main content area */
.main {
  display: flex;
  justify-content: space-between; /* Evenly distributes columns */
  align-items: flex-start; /* Aligns columns at the top */
  padding: 2rem; /* Provides padding around main content */
}

.column1,
.column3 {
  flex: 0 0 calc((100% - 4rem) * 0.15); /* 15% width, fixed */
  padding: 1rem; /* Provides padding inside each column */
}

.column2 {
  flex: 0 0 calc((100% - 4rem) * 0.7); /* 70% width, fixed */
  padding: 1rem; /* Provides padding inside column2 */
}

/* Footer styles */
.footer {
  display: flex;
  justify-content: space-between; /* Evenly distributes footer columns */
  padding: 1rem; /* Provides padding around footer content */
  background-color: antiquewhite;
}

.footer a {
  text-decoration: none; /* Remove underline from links */
  color: black; /* Set link color */
}

.footer .footercolumn {
  flex: 1; /* Each footer column takes equal space */
  padding: 0 1rem; /* Provides padding inside each footer column */
}

.footer .footercolumn h4 {
  margin-top: 0; /* Removes margin on top of heading */
}

.footer .footercolumn ul,
.footer .footercolumn p {
  margin: 0;
  padding: 0;
  list-style: none; /* Removes default list styles */
}

.footer .footercolumn ul li {
  margin: 0.5rem 0; /* Provides margin between list items */
}
```

13. Edit your App.js to the below
```javascript
import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import Header from './components/Header';
import Footer from './components/Footer';
import HomePage from './pages/Homepage';
import Biography from './pages/Biography';
import Books from './pages/Books';
import News from './pages/News';
import ContactUs from './pages/ContactUs';
import NotFound from './pages/NotFound';
import './App.css';

function App() {
  return (
    <div className="App">
      <div className="wrapper">
        <Header />
        <div className="row">
          <div className="column1"></div>
          <div className="column2">
            <Routes>
              <Route path="/" element={<HomePage />} />
              <Route path="/books" element={<Books />} />
              <Route path="/biography" element={<Biography />} />
              <Route path="/news" element={<News />} />
              <Route path="/contactus" element={<ContactUs />} />
              <Route path="*" element={<NotFound />} />
            </Routes>
          </div>
          <div className="column3"></div>
        </div>
        <Footer />
      </div>
    </div>
  );
}

function AppWrapper() {
  return (
    <Router>
      <App />
    </Router>
  );
}

export default AppWrapper;
```

14. Create 1st component /src/components/Header.js and add the below
```javascript
import React from 'react';
import { Link } from 'react-router-dom';
import logoImage from '../assets/graphics/logos/logo.png';

const Header = () => {
  return (
    <div className="header">
      <Link to="/">
        <img src={logoImage} alt="Sumeet Singh logo" className="logo" />
      </Link>
      <ul className="nav-links">
        <li><Link to="/">Home</Link></li>
        <li><Link to="/books">Books</Link></li>
        <li><Link to="/biography">Biography</Link></li>
        <li><Link to="/news">News</Link></li>
        <li><Link to="/contactus">Contact us</Link></li>
      </ul>
    </div>
  );
}

export default Header;
```

15. Create 2nd component /src/components/Footer.js and add the below
```javascript
import React from 'react';
import { Link } from 'react-router-dom';

const Footer = () => {
  return (
    <div className="footer">
      <div className="footercolumn">
        <h3>Quick links</h3>
        <ul>
          <li><Link to="/">Home</Link></li>
          <li><Link to="/books">Books</Link></li>
          <li><Link to="/biographys">Biography</Link></li>
          <li><Link to="/news">News</Link></li>
          <li><Link to="/contactus">Contact us</Link></li>
        </ul>
      </div>
      <div className="footercolumn">
        <h3>Mission</h3>
        <p>
          "To humanity I invite you to join me in a world with autonomy to augment our bodies to become better. To merge with the machine and become more than human. To join the next stage of human evolution."
        </p>
      </div>
      <div className="footercolumn">
        {/* Third column content goes here */}
      </div>
    </div>
  );
}

export default Footer;
```

16. Create 1st page /src/pages/Homepage.js and add the below
```javascript
import React from 'react';
import image1 from '../assets/graphics/me.jpeg';

const Homepage = () => {
    return (
        <div>
            <div className="main">
                <div className="column1">
                    {/* Content for left column (column1) */}
                </div>
                <div className="column2">
                    <div style={{ textAlign: 'center' }}>
                        <h1>Sumeet Singh's biography</h1>
                    </div>
                    <br />
                    <p>
                        Sumeet Singh is an author, architect, and advocate on cybernetics,
                        cyberware and cyborgs from Sydney, Australia. His ambition aspires to a
                        post-scarcity future where humans have autonomy to augment themselves in becoming
                        better by merging with machines.
                    </p>
                </div>
                <div className="column3">
                    {/* Content for right column (column3) */}
                </div>
            </div>
        </div>
    );
};

export default Homepage;

```

17. Create 2nd page /src/pages/News.js and add the below
```javascript
import React from 'react';

const News = () => {
  return (
    <div>
      <div className='main'>
        <div className="column1"></div>
        <div className="column2">
          <br />
          <br />
          <div style={{ textAlign: 'center' }}>
          <h1>News</h1>
          </div>
          <br />
          <h3>Delay with book "Cybernetics, Cyberware and Cyborgs"</h3>
          <p>Date: 06/09/2023</p>
          <p>
            Sorry everyone. I'm looking for a forward (book introduction) from a person discussed
            within the book who lives overseas that I would like to personally visit first.
          </p>
        </div>
        <div className="column3"></div>
      </div>
    </div>
  );
};

export default News;

```

18. Create 3rd page /src/pages/Biography.js and add the below
```javascript
import React from 'react';
import image1 from '../assets/graphics/biography-1.png';
import image2 from '../assets/graphics/biography-2.png';

const Biography = () => {
  return (
    <div>
      <div className="main">
        <div className="column1"></div>
        <div className="column2">
          <br />
          <br />
          <div style={{ textAlign: 'center' }}>
          <h1>Biography</h1>
          </div>
          <br />
          <p>
            Sumeet Singh, born on September 18, 1991, in Sydney, Australia, is the younger of two sons born
            to Anilta and Dalip Chand.
          </p>
          <p>
            Anilta Chand, born on January 2, 1956, in Suva, Fiji, began her professional journey after
            completing high school, initially working in the Housing Authority in Fiji. She showcased her
            diverse skill set as a legal typist, bookkeeper, and accountant. Anilta migrated to Sydney,
            Australia, on October 22, 1988, where she found employment with TUTA before Sumeet's birth.
            Throughout her life, she worked at various medical institutes, including Royal Prince Alfred
            Hospital (RPA).
          </p>
          <img src={image1} alt="Fiji Islands" style={{ maxWidth: '100%', height: 'auto' }} />
          <p>
            The Fiji islands, consisting of two major islands Vanua Levu (South) and Viti Levu (North).
          </p>
        </div>
        <div className="column3"></div>
      </div>
    </div>
  );
};

export default Biography;
```

19. Create 4th page /src/pages/ContactUs.js and add the below
```javascript
import React from 'react';
import ContactUsForm from '../components/backend/ContactUsForm';

const ContactUs = () => {
  return (
    <div>
      <div className="main">
        <div className="column1"></div>
        <div className="column2">
        <div style={{ textAlign: 'center' }}>
          <h1>Contact Us</h1>
          </div>
          <br />
          <p>
            "To humanity I invite you to join me in a world with autonomy to augment our bodies to become
            better. To merge with the machine and become more than human. To join the next stage of human
            evolution."
          </p>
          <p>Email address: kurta.kursi@gmail.com</p>
          <p>
            NOTE: Sumeet has no social media accounts. Please report and ignore any malicious social 
            media accounts claiming to be Sumeet.
          </p>
          <h3>Contact Us Form</h3>
          <ContactUsForm />
        </div>
        <div className="column3"></div>
      </div>
    </div>
  );
};

export default ContactUs;
```

20. Create 5th page /src/pages/NotFound.js and add the below
```javascript
import React from 'react';

const NotFound = () => {
  return (
    <div>
      <div className='main'>
        <div className="column1"></div>
        <div className="column2">
          <br />
          <br />
          <p>
            <div style={{ textAlign: 'center' }}>
              <h1>Page not found</h1>
            </div>
            <br />
            <p>Error 404: The page you are looking for doesn't exist. Use the search bar to navigate elsewhere.</p>
            <p>Email: kurta.kursi@gmail.com for any questions</p>
          </p>
        </div>
        <div className="column3">
        </div>
      </div>
    </div>
  );
};

export default NotFound;
```

21. Create 6th page /src/pages/SignUp.js and add the below
```javascript
import React from 'react';
import SubmitSignUp from './backend/SignUpForm';

const SignUp = () => {
  return (
    <div>
      <div className="row">
        <div className="column1"></div>
        <div className="column2">
          <h2>Online Services</h2>
          <h3>Sign Up</h3>
          <SignUpForm />
          <br />
          <br />
        </div>
        <div className="column3"></div>
      </div>
    </div>
  );
};

export default SignUp;
```

22. Create 7th page /src/pages/Login.js and add the below
```javascript
import React from 'react';
import LoginForm from './backend/LoginForm';

const Login = () => {
  return (
    <div>
      <div className="row">
        <div className="column1"></div>
        <div className="column2">
          <h2>Online Services</h2>
          <h3>Login</h3>
          <LoginForm />
          <br />
          <br />
        </div>
        <div className="column3"></div>
      </div>
    </div>
  );
};

export default SignUp;
```

23. Create 8th page /src/pages/Account.js and add the below
Include button to delete account with confirmation for full CRUD
Include button to sign up for Mailing list
```javascript
import React from 'react';
import AccountForm from '../components/backend/AccountForm';
import DeleteButton from '../components/backend/DeleteButton';

const Account = () => {
  const authToken = localStorage.getItem('authToken'); // Retrieve JWT token from localStorage
  const username = authToken ? JSON.parse(atob(authToken.split('.')[1])).username : ''; // Decode token to extract username

  return (
    <div>
      <div className="main">
        <div className="column1">
          {/* Content for left column (column1) */}
        </div>
        <div className="column2">
          <div style={{ textAlign: 'center' }}>
            <h1>Account</h1>
          </div>
          <br />
          <p>
            Welcome, {username}! {/* Display the username */}
          </p>
          <p>
            Modify your account details below
          </p>
          <AccountForm />
          <br />
          <br />
          <br />
          <p>Press the following button to delete your account</p>
          <DeleteButton />
          <br />
        </div>
        <div className="column3">
          {/* Content for right column (column3) */}
        </div>
      </div>
    </div>
  );
};

export default Account;
```

24. Create 1st backend /src/components/backend/ContactUsForm.js and add the below
Note: the below code uses formspree.com free API, however it's limited to only 2 fields
email and message. So if you copy the below change to your liking and replace the API key
```javascript
import React, { useState } from 'react';

const ContactUsForm = () => {
  const [formData, setFormData] = useState({
    email: '',
    message: ''
  });

  const [formErrors, setFormErrors] = useState({});
  const [formSubmitted, setFormSubmitted] = useState(false);

  const validateForm = () => {
    let errors = { ...formErrors };
    let isValid = true;

    // Email validation (required and valid format)
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!formData.email.trim()) {
      errors.email = 'Email is required';
      isValid = false;
    } else if (!emailRegex.test(formData.email.trim())) {
      errors.email = 'Invalid email format';
      isValid = false;
    } else {
      errors.email = '';
    }

    // Message validation (required and character limit)
    if (!formData.message.trim()) {
      errors.message = 'Message is required';
      isValid = false;
    } else if (formData.message.length > 1000) {
      errors.message = 'Message must be less than 1000 characters';
      isValid = false;
    } else {
      errors.message = '';
    }

    setFormErrors(errors);
    return isValid;
  };

  const handleInputChange = (e) => {
    const { name, value } = e.target;

    // Limit message to 1000 characters
    if (name === 'message' && value.length > 1000) {
      return;
    }

    setFormData((prevFormData) => ({
      ...prevFormData,
      [name]: value
    }));
  };

  const handleSubmit = (e) => {
    e.preventDefault();

    if (validateForm()) {
      // Form is valid, send data to Formspree endpoint
      const form = e.target;
      const formDataObj = new FormData(form);
      const xhr = new XMLHttpRequest();

      xhr.open(form.method, form.action);
      xhr.setRequestHeader('Accept', 'application/json');
      xhr.onreadystatechange = () => {
        if (xhr.readyState !== XMLHttpRequest.DONE) return;
        if (xhr.status === 200) {
          setFormSubmitted(true);
          setFormData({
            email: '',
            message: ''
          });
        } else {
          console.error('Failed to submit form');
        }
      };

      xhr.send(formDataObj);
    }
  };

  return (
    <form
      onSubmit={handleSubmit}
      action="https://formspree.io/f/mayrrrez"
      method="POST"
    >
      <div className="form-group">
        <label htmlFor="email">Your email:</label>
        <input
          type="email"
          id="email"
          name="email"
          value={formData.email}
          onChange={handleInputChange}
        />
        {formErrors.email && <span className="error">{formErrors.email}</span>}
      </div>

      <div className="form-group">
        <label htmlFor="message">Your message:</label>
        <textarea
          id="message"
          name="message"
          value={formData.message}
          onChange={handleInputChange}
        />
        {formErrors.message && <span className="error">{formErrors.message}</span>}
      </div>

      <button type="submit">Send</button>

      {formSubmitted && <p className="success-message">Thank you for your message!</p>}
    </form>
  );
};

export default ContactUsForm;

```

25. Create 2nd backend /src/components/backend/SignUpForm.js and add the below
```javascript
import React, { useState } from 'react';

const SignUpForm = () => {
    const [formData, setFormData] = useState({
        username: '',
        email: '',
        password: ''
    });

    const handleInputChange = (e) => {
        setFormData({
            ...formData,
            [e.target.name]: e.target.value
        });
    };

    const handleSubmit = (event) => {
        event.preventDefault();

        // Sending the registration data to the API endpoint
        fetch("API_URL_GOES_HERE", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(formData)
        })
        .then(response => {
            if (!response.ok) {
                throw new Error("Error: Backend signup server response was not ok");
            }
            return response.json();
        })
        .then(data => {
            console.log("Success: Registered successfully: ", data);
            alert("Success: Registration successful");
            // Redirect user to account page if registration successful
            // window.location.href = "account.html";
        })
        .catch(error => {
            console.error("Error: ", error);
            alert("Error: Registration failed. Contact support@agnisamooh.com");
        });
    };

    const togglePasswordVisibility = (e) => {
        const input = e.target.previousSibling;
        input.type = input.type === 'password' ? 'text' : 'password';
    };

    return (
        <form id="SignUpForm" onSubmit={handleSubmit}>
            <label htmlFor="username">Username:</label><br />
            <input type="text" name="username" value={formData.username} onChange={handleInputChange} maxLength="20" required /><br />
            <label htmlFor="email">Email:</label><br />
            <input type="email" name="email" value={formData.email} onChange={handleInputChange} maxLength="50" required /><br />
            <label htmlFor="password">Password:</label><br />
            <input type="password" name="password" value={formData.password} onChange={handleInputChange} maxLength="30" required /><br />
            <input type="checkbox" onClick={togglePasswordVisibility} />Show Password
            <br />
            <button type="submit">Register</button>
            <button type="reset">Reset</button>
        </form>
    );
};

export default SignUpForm;
```

26. Create 3rd backend /src/components/backend/LoginForm.js and add the below
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

27. Create 4th backend /src/components/backend/AccountForm.js and add the below
```javascript
import React, { useState } from "react";

function AccountForm() {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const [formSubmitted, setFormSubmitted] = useState(false);
    const [errorMessage, setErrorMessage] = useState('');

    const handleSubmit = async (event) => {
        event.preventDefault();
        try{
            const response = "";
            setFormSubmitted(true);
            setErrorMessage("");
        }
        catch(error) {
            console.error("Failed to update account data", error);
            setErrorMessage("Failed to update account data", error);
        }
    };

    const togglePasswordVisibility = () => {

    };

    return (
        <form onSubmit={handleSubmit}>
            <input
                type="text"
                value={username}
                onChange={(e) => setUsername(e.target.value)}
                placeholder=""
            />
            <input
                type="text"
                value={password}
                onChange={(e) => setUsername(e.target.value)}
                placeholder=""
            />
            <button type="button" onSubmit={togglePasswordVisibility}></button>
            <input>
            </input>
            <button type="submit">Update</button>
            {formSubmitted && <p className="success-message">Account details updated</p>}
            {errorMessage && <p className="error-message">{errorMessage}</p>}
        </form>
    )
};

export default AccountForm;

```

28. Create 5th backend /src/components/backend/DeleteButton.js and add the below
```javascript
import React from 'react';

const authToken = localStorage.getItem('authToken'); // Retrieve JWT token from localStorage

const DeleteButton = ({ onDelete }) => {
    const handleDelete = async () => {
        try {
            const response = await fetch('/api/user/delete', {
                method: 'DELETE',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': authToken
                }
            });
            if (!response.ok) {
                throw new Error('Failed to delete account');
            }
            onDelete(); // Optional: Implement a callback to handle UI changes after deletion
        } catch (error) {
            console.error('Delete account error:', error.message);
            // Handle error, show a message, or redirect to an error page
        }
    };

    return (
        <button onClick={handleDelete}>Delete Account</button>
    );
};

export default DeleteButton;
```

29. Create 6th backend /src/components/backend/JoinMailingList.js.js and add the below
```javascript


```

______________________________________________________________________________________________

                                CONNECT TO DATABASE
______________________________________________________________________________________________

Assuming you have a database for your website to connect to the below steps can be
modified to connect to it.

See ```mysql_commands.md``` for details on how to setup an example db for below code to
connect to.

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

1. Find a free port for backend Server.js
```bash
# MacOS, Linux
lsof -i :5000
# Windows
netstat -ano | findstr :5000

e.g, 
sumeetsingh@Sumeets-Air backend % lsof -i :5000
COMMAND   PID        USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
ControlCe 503 sumeetsingh   10u  IPv4 0x7ba65b3bbc2c31c6      0t0  TCP *:commplex-main (LISTEN)
ControlCe 503 sumeetsingh   11u  IPv6 0x147a291c7d81ae39      0t0  TCP *:commplex-main (LISTEN)


#if port is in use then find what the PID is with
ps -p 503

e.g, 
sumeetsingh@Sumeets-Air backend % ps -p 503
  PID TTY           TIME CMD
  503 ??        14:26.37 /System/Library/CoreServices/ControlCenter.app/Contents/MacOS/ControlCe

# since that port is MacOS Airplay e.g. for sharing Apple devices let's use the next port up 5001
sumeetsingh@Sumeets-Air sandbox % lsof -i :5001
sumeetsingh@Sumeets-Air sandbox % 

# since port 5001 is free lets use that
```

2. Install backend dependencies in your react project
IMPORTANT axios.delete/post etc., requires full URL e.g;
const response = await axios.post('http://localhost:5001/login', {
        username,
        password,
      });
```bash
cd src
npm install express mysql2 bcryptjs jsonwebtoken body-parser cors axios
```

3. Create a backend node.js named: src/components/backend/Server.js
using free port in variable port ```const port = 5001;```
In production environment change variable SECRET_KEY to something different
```const SECRET_KEY = "ChangeThis1!";```
```javascript
const express = require('express');
const bodyParser = require('body-parser');
const mysql = require('mysql2/promise');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const cors = require('cors');

const app = express();
const port = 5001;

const SECRET_KEY = "___YOUR_SECRET_KEY1!___";

app.use(bodyParser.json());
app.use(cors());

const dbConfig = {
  host: '127.0.0.1',
  user: 'admin',
  password: 'Password1!',
  database: 'agnisamoohdb',
};

app.get('/', (req, res) => {
  res.send('Welcome to the login server. Use the /login endpoint to log in.');
});

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

    const token = jwt.sign({ username: user.username, userId: user.userID }, SECRET_KEY, { expiresIn: '1h' });

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

4. Start the server
```bash
cd components/backend
node Server.js

e.g,
cd /Users/sumeetsingh/Documents/agnisamooh.com/src/components/backend
node Server.js
```

5. Start a new terminal window and run the website to test form
```bash
cd ../../
npm start
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


___________________________________________________________________________

                          BUILDING REACT WEBSITE
___________________________________________________________________________

1. UNCOMMENT ./build in .gitignore for CICD
In .gitignore file remove entry for ./build so that Git/VersionControl/CI/CD will detect
the build folder contents

2. TEST WEBSITE
Running below code will automatically open the website in localhost Https://127.0.0.1 to view
```bash
npm start
```

3. CREATE REACT WEBSITE
Babel: Converts the React ES6+ standard code into an older version code for multiplatform.
Webpack: Creates the website directory (/build/index.html, /html, /css, /js) to upload anywhere.
```bash
npm run build
```

4. UPLOAD WEBSITE
Follow ```AWS_website_hosting_workflow.md```