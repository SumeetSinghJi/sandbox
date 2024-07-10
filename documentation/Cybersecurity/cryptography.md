
___________________________________________________________________________

                            Cryptography
___________________________________________________________________________


FIND FILE HASH
1. Download the zip file
e.g, this 64-bit zip download for a Gameboy Advance emulator file listed here - https://visualboyadvance.org/download/vba-m/
has a listed MD5 Hash of 7D86CF059BFCDBDE40F586EFDB020099
2. 
```bash
Run Get-FileHash .\visualboyadvance-m-Win-x86_64.zip -Algorithm MD5 # Windows
# OR for different algoritms change the parameter
Run Get-FileHash .\visualboyadvance-m-Win-x86_64.zip -Algorithm SHA256 # Windows
shasum -a 1 visualboyadvance-m-Win-x86_64.zip # Unix*
md5 visualboyadvance-m-Win-x86_64.zip # Unix*

```
3. Compare the output. In this case it's the same as on the HTML page verifying the checksum is legitimate.
```bash
PS C:\Users\Sumeet\Downloads> Get-FileHash .\visualboyadvance-m-Win-x86_64.zip -Algorithm MD5
Algorithm       Hash                                                                   Path
---------       ----                                                                   ----
MD5             7D86CF059BFCDBDE40F586EFDB020099                                       
PS C:\Users\Sumeet\Downloads> Get-FileHash .\visualboyadvance-m-Win-x86_64.zip -Algorithm SHA256

Algorithm       Hash                                                                   Path
---------       ----                                                                   ----
SHA256          F656535EA605144B9444AB3DDBD93E5E3F2C27ECCC1225363787E8AB6FC092FE       
PS C:\Users\Sumeet\Downloads>
```


HASH PASSWORD
1. Create file HashPassword.js and add any password to hash
```javascript
const bcrypt = require('bcryptjs'); // FOR SHA256, change to whatever you want

const password = 'Password1!';
const saltRounds = 10;

bcrypt.hash(password, saltRounds, (err, hash) => {
  if (err) {
    console.error('Error hashing password:', err);
  } else {
    console.log('Hashed password:', hash);
  }
});
```
2. run the file with node and the output value is the hashed password that can be entered anywhere
that is encrupted with that encryption (i.e, a MySQL DB with SHA256)
```bash
sumeetsingh@Sumeets-Air backend % node HashPassword.js
Hashed password: $2a$10$9JsnQAMsal.4iMhX.CnZXuy9aCILeipHjLt8MGf5h.JJ64KSg.uOy
```