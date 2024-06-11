________________________________________________________

                    REACT WORKFLOW
________________________________________________________

Note: React files use CamelScript naming convention. Capitalise
the first letter of every word in a class and matching filename
e.g. HomePage class within HomePage.js

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
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
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
            <Route path="*" element={<NotFound />} />
          </Routes>
        </div>
        <div className="column3"></div>
        <Footer />
      </div>
    </Router>
  );
}

export default App;

```

8. Create 1st component /src/components/Header.js and add the below
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

9. Create 2nd component /src/components/Footer.js and add the below
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

10. Create 1st test page /src/components/Homepage.js and add the below
```javascript
import React from 'react';

const HomePage = () => {
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

export default HomePage;

```

11. Create 2nd test page /src/components/ContactUs.js and add the below
```javascript
import React from 'react';
import GoogleMaps from './backend/services/GoogleMaps';

const ContactUs = () => {
  return (
    <div>
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
    </div>
  );
};

export default ContactUs;
```

12. Create 3rd test page /src/components/NotFound.js and add the below
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
    </div>
  );
};

export default NotFound;
```