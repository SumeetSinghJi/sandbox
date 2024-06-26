___________________________________________________________________________

                    VANILLA HTML SITE & TAILWIND CSS
___________________________________________________________________________

1. Navigate to a new project directory
```bash
mkdir my-tailwind-website
cd my-tailwind-website
```

2. Initialise a new project
```bash
npm init -y
npm install -D tailwindcss
```

3. Create a new tailwind configuration file
```bash
npx tailwindcss init
```

4. Add code below to tailwind.config.js
```javascript
// tailwind.config.js
module.exports = {
  content: ["./**/*.html"],
  theme: {
    extend: {},
  },
  plugins: [],
};

```

5. Create a styles.css with code below
```css
/* styles.css */
@tailwind base;
@tailwind components;
@tailwind utilities;
```

6. Create a index.html file with code below
```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Hello World with Tailwind CSS</title>
  <link href="styles.css" rel="stylesheet">
</head>
<body class="bg-gray-100 flex items-center justify-center h-screen">
  <div class="text-center">
    <h1 class="text-4xl font-bold text-gray-800">Hello World</h1>
    <p class="text-lg text-gray-600 mt-4">Welcome to your first Tailwind CSS webpage!</p>
  </div>
</body>
</html>
```

7. Build your css file
```bash
npx tailwindcss -i ./styles.css -o ./output.css --watch
```

8. Include the new output in your index.html
```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Hello World with Tailwind CSS</title>
  <link href="output.css" rel="stylesheet">
</head>
<body class="bg-gray-100 flex items-center justify-center h-screen">
  <div class="text-center">
    <h1 class="text-4xl font-bold text-gray-800">Hello World</h1>
    <p class="text-lg text-gray-600 mt-4">Welcome to your first Tailwind CSS webpage!</p>
  </div>
</body>
</html>
```

9. Start the index.html to view your website



___________________________________________________________________________

                         REACT + TAILWIND CSS
___________________________________________________________________________

1. Install tailwind in react
```bash

```

2. Use tailwind in react
```javascript

```