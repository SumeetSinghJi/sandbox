import React from 'react';

const Footer = () => {
    return (
        <div className="footer">
            <div className="footercolumn1">
                <h3>Quick links</h3>
                <ul>
                    <li><Link to="/">Home</Link></li>
                    <li><Link to="/Cytheseus">Cytheseus</Link></li>
                    <li><Link to="/News">News</Link></li>
                    <li><Link to="/Contactus">Contact us</Link></li>
                    <li><Link to="/Signup">Sign up</Link></li>
                    <li><Link to="/PrivacyPolicy">Privacy policy</Link></li>
                    <li><Link to="/RefundAndReturnPolicy">Returns policy</Link></li>
                    <li><Link to="/TermsAndConditions">Terms and Conditions</Link></li>
                    <li><Link to="/PromotionalContent">Promotional Content</Link></li>
                    <li><Link to="/Unsubscribe">Unsubscribe</Link></li>
                </ul>
            </div>
            <div className="footercolumn2">
                <h3>Contact us</h3>
                <p>
                    Contact us<br />
                    Call us on: 0452 008 019<br />
                    International dial<br />
                    +61 452 008 019<br />

                    Address (on appointment): B1/13-21 Mandible St Alexandria NSW 2015, Australia<br />

                    Our Email: support@sabrenetics.com<br />

                    ABN: 89 655 184 946<br />

                    ACN: 655 184 946<br />
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