___________________________________________________________________________

                    COMMON COMMANDS
___________________________________________________________________________

1. Install node.js
```bash
Windows: winget install Node.js
MacOS: brew install node
Linux: apt install node
```

2a. (OPTIONAL) If cloning React website for first time
if the /node_modules is missing the dependencies to run the app
you will first need to cd into folder with file package.json then run the below
to create the node_modules folder. Then skip to START WEBSITE step
```bash
npm install
```

2b. (OPTIONAL) - RESET/CLEAR NPM CACHE
```bash
npm cache clean --force
```

3a. INSTALL LIBS - CWD e.g, ```C:\Users\<YourUsername>\Documents\My-React-Website\node_modules```
# The recommended approach. You can just use a .gitignore to exclude these files from version control
# but keep them within this space so it's easier to port across different computers to work from
# without rebuilding your environment
```bash
npm install react-router-dom, create-react-app

```
3b. INSTALL LIBS - GLOBALLY e.g. ```C:\Users\<YourUsername>\AppData\Roaming\npm\node_modules```
```bash
npm install -g react-router-dom, create-react-app
```

4. RUNNING LIB TO CREATE REACT WEBSITE TEMPLATE
# This will setup a template react website in current working directory. You can test with npm start within
```bash
create-react-app my-app
```

5. START WEBSITE FOR TESTING LOCALLY
# If any errors they will display in webpage, fix before building and try again
```bash
npm start
```

4. CONVERT REACT WEBSITE TO STATIC PAGES IN ./Build
# for hosting e.g, uploading in Godaddy to host website
```bash
npm run build
```