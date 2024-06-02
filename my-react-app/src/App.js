// src/App.js
import React from 'react';
import ThreeScene from './components/ThreeScene';
import Header from './components/Header';
import Footer from './components/Footer';
import './App.css';

function App() {
  return (
    <div className="App">
      <Header />
      <ThreeScene />
      <Footer />
    </div>
  );
}

export default App;
