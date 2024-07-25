
______________________________________________________________________________________________

                                        PROFILE SCRIPT
______________________________________________________________________________________________

1. CLEAR SCREEN
```bash
import os; cls = lambda: os.system('cls' if os.name == 'nt' else 'clear')

# EXAMPLE
> python3
"Hello sumeet@sumeets-pc the date is 18/07/2024"
>>> cls()
0
>>>
```

______________________________________________________________________________________________

                                        COMMON COMMANDS
______________________________________________________________________________________________


LIBRARY LOCATIONS
```bash
C:\Python\Lib\site-packages # system wide
C:\Users\YourUsername\AppData\Roaming\Python\PythonXY\site-packages # virtual env
```


INSTALL LIBRARY
```bash
pip3 install torch #short for pytorch

> ls C:\Python\Lib\site-packages
torch
```

______________________________________________________________________________________________

                                    SCRIPTS - IMPORTS
______________________________________________________________________________________________

IMPORTS allow persistent use of functions globally within a python session, similar to C++ headers

NOTE: when you create an import script then load it in a python session and run it, it will
create a ```./_pycache_``` directory. You can delete it with no impact, safely, anytime.

1. CREATE IMPORT SCRIPT
```python
# ./clear.py
import os
cls = lambda: os.system('cls' if os.name == 'nt' else 'clear')
```

2. IMPORT IN PYTHON SESSION TO USE
```python
from clear import cls

# EXAMPLE
>>> cls()
0
```

