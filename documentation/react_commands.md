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

The steps below will create a website with 
* Account details form page
* Contact us form page
* Shopping cart form page

to create the AWS RDS database see ```MySQL_commands```
to create the AWS lambda and API's see ```AWS_website_hosting_commands.md```

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

9. Create all folders
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

11. GENERATE AND ADD API TO NEW FILE
e.g. Follow ```AWS_Lambda_commands.md``` to create API's for GET/POSTing account details then replace below default API keys
```bash
echo '
// Import example
// import { API_POST_SIGNUP_URL, API_GET_USER_URL, API_DELETE_USER_URL } from './config';
// Usage example
// console.log(API_POST_SIGNUP_URL);

export const API_POST_SIGNUPFORM = "https://v4a9f9qoml.execute-api.ap-southeast-2.amazonaws.com/default/sumeet-singh-database_signupform";

export const API_POST_LOGINFORM = "https://v4a9f9qoml.execute-api.ap-southeast-2.amazonaws.com/default/sumeet-singh-database-loginform";

export const API_POST_REPLACEACCOUNTDETAILS = "https://v4a9f9qoml.execute-api.ap-southeast-2.amazonaws.com/default/sumeet-singh-database-replaceaccountdetails";

export const API_GET_ACCOUNTDETAILS = "https://v4a9f9qoml.execute-api.ap-southeast-2.amazonaws.com/default/sumeet-singh-database-getaccountdetails";
' > config.js
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

20. Create 6th page /src/pages/NotFound.js and add the below
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

21. Create 5th page /src/pages/SignUp.js and add the below
```javascript
import React from 'react';
import SubmitSignUp from './backend/SubmitSignUp';
import LoginForm from './backend/LoginForm';

const SignUp = () => {
  return (
    <div>
      <div className="row">
        <div className="column1"></div>
        <div className="column2">
          <h2>Online Services</h2>
          <h3>Create new account</h3>
          <SignUpForm />
          <br />
          <br />
          <h3>Login</h3>
          <LoginForm />
        </div>
        <div className="column3"></div>
      </div>
    </div>
  );
};

export default SignUp;
```

22. Create 7th page /src/pages/Account.js and add the below
```javascript
import React from 'react';

const Account = () => {
  return (
    <div>
      <div className="column1"></div>
      <div className="column2">
        <br />
        <br />
        <p>
          <h2>Account</h2>
          <p>Account details</p>
        </p>
      </div>
      <div className="column3"></div>
    </div>
  );
};

export default Account;
```

23. Create 1st backend /src/components/backend/SignUpForm.js and add the below
```javascript
import React, { useState } from 'react';
import API_POST_SIGNUP_URL from '../../config';

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
        fetch(API_URL, {
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

24. Create 2nd backend /src/components/backend/LoginForm.js and add the below
```javascript
import React, { useState } from 'react';

const LoginForm = () => {
    const [formData, setFormData] = useState({
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

        // Your login logic using formData
    };

    const togglePasswordVisibility = (e) => {
        const input = e.target.previousSibling;
        input.type = input.type === 'password' ? 'text' : 'password';
    };

    return (
        <form id="loginForm" onSubmit={handleSubmit}>
            <label htmlFor="email">Email:</label><br />
            <input type="email" name="email" value={formData.email} onChange={handleInputChange} required /><br />
            <label htmlFor="password">Password:</label><br />
            <input type="password" name="password" value={formData.password} onChange={handleInputChange} required /><br />
            <input type="checkbox" onClick={togglePasswordVisibility} />Show Password
            <br />
            <button type="submit">Login</button>
            <button type="reset">Reset</button>
        </form>
    );
};

export default LoginForm;
```

25. Create 3rd backend /src/components/backend/ContactUsForm.js and add the below
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

26. Create 4th backend /src/components/backend/GetAccountDetails.js and add the below
```javascript
const express = require('express');
const router = express.Router();
const authMiddleware = require('../middleware/authMiddleware');
const User = require('../models/User'); // Assuming you have a User model

// GET /api/user/profile
router.get('/profile', authMiddleware, async (req, res) => {
    try {
        // Fetch user details based on authenticated user (from JWT)
        const user = await User.findById(req.user.id).select('-password'); // Excluding password field
        if (!user) {
            throw new Error('User not found');
        }
        res.json(user);
    } catch (err) {
        res.status(404).json({ error: err.message });
    }
});

module.exports = router;

```

27. Create 5th backend /src/components/backend/ReplaceAccountDetailsForm.js and add the below
```javascript
```

28. In .gitignore file remove entry for ./build so that Git/VersionControl/CI/CD will detect
the build folder contents

29. CONVERT REACT WEBSITE TO STATIC PAGES IN ./build
for hosting e.g, uploading in Godaddy to host website
```bash
npm run build
```

30. START WEBSITE FOR TESTING LOCALLY
```bash
npm start
```

31. UPLOAD WEBSITE
Follow ```AWS_website_hosting_workflow.md```