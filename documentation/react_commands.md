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
# will initialise git, create .gitignore configured to ignore node_modules. Ready to commit
```bash
create-react-app sumeet-singh.com
```

4. MOVE INTO PROJECT
```bash
cd sumeet-singh.com
```

5. INSTALL LIBS IN PROJECT DIRECTORY
# Example on Windows: C:\Users\<YourUsername>\Documents\sumeet-singh.com\node_modules
# Example on MacOS: /Users\<YourUsername>\Documents\sumeet-singh.com\node_modules
```bash
npm install react-router-dom
```

6. START WEBSITE FOR TESTING LOCALLY
```bash
npm start
```

7. CD TO SRC
```bash
cd src
```

8. Create all folders
```bash
mkdir assets # for assets e.g. graphics, sounds, images, videos to display on webpage
mkdir assets/graphics
mkdir assets/graphics/icons
mkdir assets/sounds
mkdir pages # for pages e.g. homepage.js, contactus.js, news.js
mkdir components # for reusable assets e.g. header.js, footer.js
mkdir backend # for backend code e.g. SubmtiSignUp.js, SubmitLogin.js
```

9. REPLACE DEFAULT FAVICON
```bash
cp path_to_your_favicon.ico /public/favicon.ico
```

10. GENERATE AND ADD API TO NEW FILE
# e.g. Follow ```AWS_Lambda_commands.md``` to create an API then replace below command with key
```bash
echo 'const API_POST_SIGNUP_URL = "https://v4a9f9qoml.execute-api.ap-southeast-2.amazonaws.com/default/agnisamooh-database-connect"; export default API_POST_SIGNUP_URL;' > config.js
```

11. REPLACE DEFAULT CSS /src/App.css
```css
```

12. Edit index.js to the below
```javascript
import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import App from './App';
import reportWebVitals from './reportWebVitals';

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>
);

reportWebVitals();
```

13. Edit your App.js to the below
```javascript
import React from 'react';
import { BrowserRouter as Router, Route, Routes, useLocation } from 'react-router-dom';
import Header from './components/Header';
import Footer from './components/Footer';
import HomePage from './components/HomePage';
import Games from './components/Games';
import News from './components/News';
import ContactUs from './components/ContactUs';
import SignUp from './components/SignUp';
import PrivacyPolicy from './components/PrivacyPolicy';
import RefundAndReturnPolicy from './components/RefundAndReturnPolicy';
import TermsAndConditions from './components/TermsAndConditions';
import PromotionalContent from './components/PromotionalContent';
import Unsubscribe from './components/Unsubscribe';
import Account from './components/Account';
import Cart from './components/Cart';
import Checkout from './components/Checkout';
import NotFound from './components/NotFound';
import './App.css';

function App() {
  const location = useLocation();
  const excludePaths = ['/cart', '/checkout'];

  return (
    <div className="App">
      {!excludePaths.includes(location.pathname) && <Header />}
      <div className="column1"></div>
      <div className="column2">
        <Routes>
          <Route path="/" element={<HomePage />} />
          <Route path="/games" element={<Games />} />
          <Route path="/news" element={<News />} />
          <Route path="/contactus" element={<ContactUs />} />
          <Route path="/signup" element={<SignUp />} />
          <Route path="/privacypolicy" element={<PrivacyPolicy />} />
          <Route path="/refundandreturnpolicy" element={<RefundAndReturnPolicy />} />
          <Route path="/termsandconditions" element={<TermsAndConditions />} />
          <Route path="/promotionalcontent" element={<PromotionalContent />} />
          <Route path="/unsubscribe" element={<Unsubscribe />} />
          <Route path="/account" element={<Account />} />
          <Route path="/cart" element={<Cart />} />
          <Route path="/checkout" element={<Checkout />} />
          <Route path="*" element={<NotFound />} />
        </Routes>
      </div>
      <div className="column3"></div>
      {!excludePaths.includes(location.pathname) && <Footer />}
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

___________________________________________________________________________

                          CREATE COMPONENTS
___________________________________________________________________________


14. Create 1st component /src/components/Header.js and add the below
```javascript
import React from 'react';
import { Link } from 'react-router-dom';
import logoImage from '../assets/graphics/logos/FireGroup_Logo_PNG_4097px.png';

const Header = () => {
  return (
    <div className="header">
      <Link to="/">
        <img src={logoImage} alt="AgniSamooh logo" style={{ width: '250px', height: '100px' }} />
      </Link>
      <h2>AgniSamooh</h2>
      <ul>
        <li><Link to="/">Home</Link></li>
        <li><Link to="/news">News</Link></li>
        <li><Link to="/downloads">downloads</Link></li>
        <li><Link to="/contactus">Contact us</Link></li>
        <li><Link to="/cart"><i className="fa-solid fa-cart-shopping fa-xl"></i></Link></li>
        <li><Link to="/account"><i className="fa-solid fa-user fa-xl"></i></Link></li>
      </ul>
    </div>
  );
}

export default Header;
```

15. Create 2nd component /src/components/Footer.js and add the below
```javascript
import React from 'react';
import { Link } from 'react-router-dom'; // Import Link from React Router

const Footer = () => {
    return (
        <div className="footer">
            <div className="footercolumn1">
                <h3>Quick links</h3>
                <ul>
                    <li><Link to="/">Home</Link></li>
                    <li><Link to="/games">Games</Link></li>
                    <li><Link to="/news">News</Link></li>
                    <li><Link to="/contactus">Contact us</Link></li>
                    <li><Link to="/signup">Sign up</Link></li>
                    <li><Link to="/privacypolicy">Privacy policy</Link></li>
                    <li><Link to="/refundandreturnpolicy">Returns policy</Link></li>
                    <li><Link to="/termsandconditions">Terms and Conditions</Link></li>
                    <li><Link to="/promotionalcontent">Promotional Content</Link></li>
                    <li><Link to="/unsubscribe">Unsubscribe</Link></li>
                </ul>
            </div>
            <div className="footercolumn2">
                <h3>Contact us</h3>
                <p>
                    Address: NSW, 2018, Australia<br />
                    Phone: 0411 111 111<br />
                    Hours of Operations: This is a fictional website learning project. Not a real business.<br />
                    Email: support@agnisamooh.com
                </p>
            </div>
            <div className="footercolumn3">
                <div className="centre_text">
                    <h3>Accepted payment methods</h3>
                    <p>
                        Mastercard, Visa, Bitcoin, Ethereum<br />
                        <i className="fa-solid fa-credit-card fa-xl"></i>
                        <i className="fa-brands fa-bitcoin fa-xl"></i>
                        <i className="fa-brands fa-ethereum fa-xl"></i>
                    </p>
                </div>
            </div>
        </div>
    );
}

export default Footer;
```

16. Create 1st page /src/pages/Homepage.js and add the below
```javascript
import React from 'react';

const Error = () => {
  return (
    <div>
      <div className="row">
        <div className="column1"></div>
        <div className="column2">
        <div className="centre_text"><b>This is a fictional website learning project</b></div>
          <br />
          <br />
          Agnisamooh.com is a global gaming community aspiring to grow with indie members of diverse castes
          all around the world. We hope to have a curated source for gamers of minority communities as well as
          anyone to have a promotional place to showcase their culture to the world.
          <br />
          <br />
          We invite passionate game developers and enthusiasts to join us in building a platform where creativity and
          collaboration thrive. Agni is Sanskrit for Fire, and Samooh for Group.
          Together they spell AgniSamooh translated to FireGroup.
          <br />
          <br />
          Sanskrit is an ancient language said to be well developed for programming code, and this community brings ancient wisdom to new age
          gamers. The word represents the collective community of game developers all around the world to have
          a universal space open to the community. We aim to bring about Gaming as a hobby to areas of the
          world in strife to bring about peaceful hobbies in harsh environments. We believe there are new
          ideas for worlds, stories, and games that people globally haven't experienced from unique cultures
          and perspectives. Thus AgniSamooh was born.
          <br />
          <br />
          <div className="centre_text"><b>Submit Your Games</b></div>
          <br />
          <br />
          We encourage game developers to contribute by submitting their creations. You can easily share your
          games by linking your Github repositories, Itch.io pages, or any other repositories or executables. We
          believe in the power of open collaboration, and your games are a valuable addition to our collection.
          <br />
          <br />
          <div className="centre_text"><b>Play, Share, and Download</b></div>
          <br />
          <br />
          At Agnisamooh.com, you can play, share, and download games from a diverse range of developers. Explore
          new worlds, discover innovative gameplay, and connect with fellow gamers. It's all about community and a
          love for gaming.
          <br />
          <br />
          <div className="centre_text"><b>Volunteers Needed</b></div>
          <br />
          <br />
          We are actively seeking volunteers to help maintain and moderate this website. If you're passionate
          about gaming and want to contribute to our community, consider joining us. Your efforts will play a
          crucial role in keeping this platform a welcoming and enjoyable space for all. Please reach out to us
          through the contact information provided on the website if you're interested in volunteering. Together,
          we can make Agnisamooh.com even better!
          <br />
          <br />
        </div>
        <div className="column3"></div>
      </div>
    </div>
  );
};

export default Error;

```

17. Create 2nd page /src/pages/News.js and add the below
```javascript
import React from 'react';

const NotFound = () => {
  return (
    <div>
      <div className="column1"></div>
      <div className="column2">
        <br />
        <br />
        <p>
          <h2>Page not found</h2>
          <p>Error 404: The page you are looking for doesn't exist. Use the search bar to navigate elsewhere.</p>
          <p>Email: kurta.kursi@gmail.com for any questions</p>
        </p>
      </div>
      <div className="column3"></div>
    </div>
  );
};

export default NotFound;
```

18. Create 3rd page /src/pages/Downloads.js and add the below
```javascript
import React from 'react';

const NotFound = () => {
  return (
    <div>
      <div className="column1"></div>
      <div className="column2">
        <br />
        <br />
        <p>
          <h2>Page not found</h2>
          <p>Error 404: The page you are looking for doesn't exist. Use the search bar to navigate elsewhere.</p>
          <p>Email: kurta.kursi@gmail.com for any questions</p>
        </p>
      </div>
      <div className="column3"></div>
    </div>
  );
};

export default NotFound;
```

19. Create 4th page /src/pages/ContactUs.js and add the below
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

20. Create 5th page /src/pages/NotFound.js and add the below
```javascript
import React from 'react';

const NotFound = () => {
  return (
    <div>
      <div className="column1"></div>
      <div className="column2">
        <br />
        <br />
        <p>
          <h2>Page not found</h2>
          <p>Error 404: The page you are looking for doesn't exist. Use the search bar to navigate elsewhere.</p>
          <p>Email: kurta.kursi@gmail.com for any questions</p>
        </p>
      </div>
      <div className="column3"></div>
    </div>
  );
};

export default NotFound;
```

21. Create 5th page /src/pages/Cart.js and add the below
```javascript
import React from 'react';

const NotFound = () => {
  return (
    <div>
      <div className="column1"></div>
      <div className="column2">
        <br />
        <br />
        <p>
          <h2>Shopping cart</h2>
          <p>Add items to cart</p>
        </p>
      </div>
      <div className="column3"></div>
    </div>
  );
};

export default NotFound;
```

22. Create 5th page /src/pages/Account.js and add the below
```javascript
import React from 'react';

const NotFound = () => {
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

export default NotFound;
```

21. Create 1st backend /src/components/backend/SignUpForm.js and add the below
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

22. Create 2nd backend /src/components/backend/LoginForm.js and add the below
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

23. Create 3rd backend /src/components/backend/ContactUsForm.js and add the below
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

24. Create 4th backend /src/components/backend/GetAccount.js and add the below
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

25. Create 5th backend /src/components/backend/ReplaceAccountForm.js and add the below
```javascript
```

26. CONVERT REACT WEBSITE TO STATIC PAGES IN ./Build
# for hosting e.g, uploading in Godaddy to host website
```bash
npm run build
```

___________________________________________________________________________

                    HOSTING WEBSITE
___________________________________________________________________________

Read ```AWS_website_hosting_workflow.md``` on details how to host this react website
to be available online.