import React from 'react';
import { Link } from 'react-router-dom';
import logoImage from '../assets/graphics/logos/Logo_PNG_RGB.png';

const Header = () => {
    return (
        <div className='header'>
            <Link to="/">
                <img src={logoImage} alt = "Sabrenetics logo" style={{width: '250px', height:'100px'}} />
            </Link>
            <h2>Cytheseus</h2>
            <ul>
                <li><Link to="/">Home</Link></li>
                <li><Link to="/Cytheseus">Games</Link></li>
                <li><Link to="/news">News</Link></li>
                <li><Link to="/contactus">Contact us</Link></li>
                <li><Link to="/cart"><i className="fa-solid fa-cart-shopping fa-xl"></i></Link></li>
                <li><Link to="/signup"><i className="fa-solid fa-user fa-xl"></i></Link></li>
            </ul>
        </div>
    );
}
