________________________________________________________

                    REACT WORKFLOW
________________________________________________________

Note: all .js files should start with capital letter e.g. Footer.js
to match best practice class naming conventions

1. SETUP REACT
```bash
npm install react-router-dom, create-react-app
```

2. INITIALISE WEBSITE
```bash
create-react-app my-app
```

3. Create assets folder under /src e.g. /my-app/src/assets
put all your assets here e.g. assets/graphics, videos, documents

4. Create components folder under /src e.g. /my-app/src/components
This holds your page includes e.g. footer, header, contactus, etc.,

5. Add your css to /src/App.css

6. Edit index.js to the below
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

7. Edit your App.js to the below
```javascript
import React from 'react';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
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
import NotFound from './components/NotFound';

function App() {
  return (
    <Router>
      <div className="App">
        <Header />
        <div className="column1"></div>
        <div className="column2">
          <Switch>
            <Route exact path="/" component={HomePage} />
            <Route path="/games" component={Games} />
            <Route path="/news" component={News} />
            <Route path="/contactus" component={ContactUs} />
            <Route path="/signup" component={SignUp} />
            <Route path="/privacypolicy" component={PrivacyPolicy} />
            <Route path="/refundandreturnpolicy" component={RefundAndReturnPolicy} />
            <Route path="/termsandconditions" component={TermsAndConditions} />
            <Route path="/promotionalcontent" component={PromotionalContent} />
            <Route path="/unsubscribe" component={Unsubscribe} />
            <Route component={NotFound} />
          </Switch>
        </div>
        <div className="column3"></div>
        <Footer />
      </div>
    </Router>
  );
}

export default App;
```

8. Create a /src/components/Header.js and add the below
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
        <li><Link to="/games">Games</Link></li>
        <li><Link to="/news">News</Link></li>
        <li><Link to="/contactus">Contact us</Link></li>
        <li><Link to="/cart"><i className="fa-solid fa-cart-shopping fa-xl"></i></Link></li>
        <li><Link to="/signup"><i className="fa-solid fa-user fa-xl"></i></Link></li>
      </ul>
    </div>
  );
}

export default Header;
```

9. Create a /src/components/Footer.js and add the below
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

10. Create 1st test page Homepage.js
```javascript
import React from 'react';
import Header from './Header';
import Footer from './Footer';

const Error = () => {
  return (
    <div>
      <Header />
      <div className="row">
        <div className="column1"></div>
        <div className="column2">
          <h2>Page not found</h2>
          <p>Error 404: The page you are looking for doesn't exist. Use the search bar to navigate elsewhere.</p>
          <p>Email: kurta.kursi@gmail.com for any questions</p>
        </div>
        <div className="column3"></div>
      </div>
      <Footer />
    </div>
  );
};

export default Error;
```

11. Create 2nd test page ContactUs.js
```javascript
import React from 'react';
import Header from './Header';
import Footer from './Footer';
import GoogleMaps from './backend/services/GoogleMaps';

const ContactUs = () => {
  return (
    <div>
      <Header />
      <div className="row">
        <div className="column1"></div>
        <div className="column2">
          <h2>Contact us</h2>
          <br />
          <h2>CONTACT US FORM</h2>
          <br />
          <form id="contactus" action="https://formspree.io/f/xeqbdzpn" method="POST">
            <label htmlFor="first_name">First name:</label><br />
            <input type="text" id="first_name" name="first_name" maxLength="20" /><br />
            <label htmlFor="last_name">Last name:</label><br />
            <input type="text" id="last_name" name="last_name" maxLength="20" /><br />
            <label htmlFor="email">Email:</label><br />
            <input type="text" id="email" name="email" maxLength="20" /><br />
            <label htmlFor="mobile">Mobile:</label><br />
            <input type="tel" id="mobile" name="mobile" maxLength="15" /><br />
            <label htmlFor="subject">Subject</label><br />
            <input type="text" id="subject" name="subject" maxLength="200" /><br />
            <label htmlFor="message">Message</label><br />
            <textarea id="message" name="subject" placeholder="Type your message here..."></textarea>
            <br />
            <input type="submit" value="send" />
            <input type="reset" value="reset" />
            <div id="submissionConfirmation">Your message has been sent.</div>
          </form>
          <br />
          <br />
          <h3>Find us below</h3>
          This is a fictional website learning project open source community website with no fixed location.
          <br />
          <br />
          Address: NSW, 2018, Australia
          <br />
          Phone: 0411 111 111
          <br />
          Hours of Operations: This is a fictional website learning project.
          <br />
          Email: support@agnisamooh.com
          <br />
          <br />
          <GoogleMaps />
          <br />
          <br />
          <br />
          <h2>Subscribe to Company updates</h2>
          <form id="contactus" action="https://formspree.io/f/xwkdzqak" method="POST">
            <label htmlFor="email">Email:</label><br />
            <input type="text" id="email" name="email" maxLength="20" /><br />
            <br />
            <input type="submit" value="send" />
            <div id="submissionConfirmation">You have signed up successfully.</div>
          </form>
          <br />
          <br />
        </div>
        <div className="column3"></div>
      </div>
      <Footer />
    </div>
  );
};

export default ContactUs;
```

12. Create 3rd test page NotFound.js and add the below
```javascript
import React from 'react';
import Header from './Header';
import Footer from './Footer';

const NotFound = () => {
  return (
    <div>
      <Header />
      <div className="column1"></div>
      <div className="column2">
        <br />
        <br />
        <p>
          <div className="centre_text"><b>ERROR: 404 FILE NOT FOUND</b></div>
          <br />
          <br />
          Error: The page you are looking for does not exist or is mispelt. Please use the search
          option to type the webpage you are searching for and click search. Similar results will
          be displayed for your selection.
          <br />
          <br />
        </p>
      </div>
      <div className="column3"></div>
      <Footer />
    </div>
  );
};

export default NotFound;
```