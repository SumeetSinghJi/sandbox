___________________________________________________________________________

                          EXAMPLE FLEX CSS
___________________________________________________________________________

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

body html #root{
  font-family: Arial, sans-serif; /* if Arial isn't available on browser, use next font*/
  display: flex; /*make the body all flex*/
  padding: 0;
  margin: 0;
  height: 100%;
  box-sizing: border-box
}
.wrapper {
  display: flex; /* Wraps children in flex e.g,  <div className="wrapper"><header><footer><main></wrapper>*/
  flex-direction: column; /* Stacks the children of the .wrapper (header, main, and footer) vertically. */
  min-height: 100vh;
}
header {
  display: flex;
  justify-content: space-between; /* makes logo on left, and nav links on right */
  align-items: center; /* elements e.g. logo are vertically centered in header */
  padding: 1rem; /* scale the padding to font-size. If browser font size is increased by user
  then the padding will grow. So for bad eyesight people increasing browser font, spaces everything out. padding in this case means the distance from the elements to the edges of the header */
}
header .logo {
    width: 100px;
    height: auto; /* Maintain aspect ratio */
}

header nav{
  display: flex;
  gap: 1rem; /* Whereas padding defines the distances between the element and the outer edge, gap
  is specific to flex that defines the gap between flex objects */
}
header nav a{
  text-decoration: none; /* remove default underline that browsers add to html links */
}
header nav a:hover{
  text-decoration: underline; /* hovering over link adds underline */
}
main {
  display: flex;
  padding: 2rem;
  background-color: #f5f5f5;
}
footer {
  display: flex;
  justify-content: space-around;
  padding: 1rem;
}

footer .column {
  flex: 1;
  padding: 0 1rem;
}

footer .column h4 {
    margin-top: 0;
}

footer .column p, footer .column ul {
    margin: 0;
    padding: 0;
    list-style: none;
}

footer .column ul li {
    margin: 0.5rem 0;
}
```