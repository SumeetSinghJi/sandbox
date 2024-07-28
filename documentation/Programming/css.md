
# PROGRAMMING WITH GIT

By: Sumeet Singh @ sumeet-singh.com

Date: July 2024

# TABLE OF CONTENTS
- [1. Requirements](#requirements)
- [2. Installing](#installing)
- [3. Profile script](#profile-script)
- [4. Common Commands](#common-commands)
- [5. Scripts - Example Flex CSS](#scripts-example-flex-css)

# REQUIREMENTS

# INSTALLING

# PROFILE SCRIPT

# COMMON COMMANDS

# SCRIPTS EXAMPLE FLEX CSS

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


