
# PROGRAMMING WITH PYTHON

By: Sumeet Singh @ sumeet-singh.com

Date: July 2024

# TABLE OF CONTENTS
- [1. Requirements](#requirements)
- [2. Installing](#installing)
- [3. Profile script](#profile-script)
- [4. Common Commands](#common-commands)
- [5. Importing scripts](#importing-scripts)
- [6. Drawing Images with Matplotlib](#drawing-images-with-matplotlib)
- [7. What is AI](#what-is-ai)
- [7a. Training a Neural Network](#training-a-neural-network)
- [7b. Creating a AI personal assistant](#creating-a-ai-personal-assistant)

# REQUIREMENTS
Python is lightweight and can be installed on many devices, some even have them already installed

# INSTALLING
This code uses Python 3. Some devices already come with python3 so test by
calling it directly in your shell with ```python3``` If not available you can install 
it from many os repos with commands below;
```bash
apt-cache install python3 # linux
brew install python3 # mac
winget install python3 # windows

> python3 # to start python 3

Welcome to Python...
```

# PROFILE SCRIPT

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

# COMMON COMMANDS

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

# IMPORTING SCRIPTS

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

# DRAWING IMAGES WITH MATPLOTLIB

1. DRAW & EXPORT IMAGE
```python
import matplotlib.pyplot as plt # for drawing text to window
import matplotlib.patches as patches # for drawing shapes to window

# Set size here e.g, A4 paper dimensions in inches
a4_width = 8.27
a4_height = 11.69

# Create a figure and axis using previous defined dimensions
fig, ax = plt.subplots(figsize=(a4_width, a4_height))

# Set background color
fig.patch.set_facecolor('black')
ax.set_facecolor('black')

# Add the header text
header_text = "To change game press"
ax.text(0.5, 0.8, header_text, color='white', fontsize=30, ha='center', va='center', fontweight='bold')

# Add the instruction text with multiple lines
instruction_text = "Joystick: P1 + P2\nController: (PS) button + Start"
ax.text(0.5, 0.5, instruction_text, color='yellow', fontsize=25, ha='center', va='center', fontweight='bold')

# Create Pac-Man shape (yellow circle with a triangle cutout)
pacman_circle = patches.Wedge((0.5, 0.1), 0.1, 30, 330, facecolor='yellow', edgecolor='yellow')

# Add Pac-Man shape to the plot
ax.add_patch(pacman_circle)

# Remove/hide axes lines
ax.axis('off')

# Save the poster as a PDF
plt.savefig('arcade_poster.pdf', format='pdf', bbox_inches='tight')

# Display the poster
plt.show()
```

# WHAT IS AI?

Lesson 1 - https://www.youtube.com/watch?v=TkwXa7Cvfr8 

A neural network can be viewed as a function f(x)≈NN(x) that maps inputs (x) to outputs (y) through a series of transformations. This function is learned from training data.

An example is using pandas to import some data such as housing prices this year in Sydney, Australia, using
huggingfaces transformation library to connect to an LLM such as ChatGPT which is the neural network, 
and then use pytorch's torch import library to connect to the LLM and find predictions.

When you download a LLM such as with using huggingfaces simple code to import, then the LLM's such as ChatGPT2
already come with their weights as part of the file size. You can feed it more data if you wish, or use as is
to answer questions which is called Natural Language Processing (NLP). Using the existing trained LLM this way
is called inference which means using a LLM model after it's been trained.

A Neural network = NN(x) = f(x)

x1>  <y1
x2>><<y2
x3>><<y3
x4>  <y4

The first step of a neural network is getting all the inputs in a vector which produce 1 output
e.g.
Features
|x1|
|x2|
|x3|

each input is multiplied by it's own weight + a bias added to the end
= w1x1 + w2x2 + w3x3 + w4 (bias)

written as linear algerbra lets times each input by it's weight to find dot product

|x1| |w1|
|x2|*|w2|
|x3| |w3|
|1|  |w4|
(bias is assumed to be 1)

Let's make up some example values
|0.3| | 0.2|   | 0.06|
|1.8|*|-0.4| = |-0.72| = -0.26 = Dot Product
|0.5| | 0.6|   | 0.3 |
|1.0| | 0.1|   | 0.1 |

Dot product is then passed to an activation function ReLU(-0.26) which returns 0

which looks like this in a function graphy/cardassian coordinate system like a Sin Wave y = Sin(x)

                      |       *
                      |     *
                      |   *
                      | *
***********************___________________________x
                      |
                      |
                      |
                      |y

each layer of the neural network has it's own weights and it's out outputs forming different dot product points
until we get the final output of the network. Each neuron forms their own points to build their own points
to make a neural network that can learn and prove any function e.g. enough inputs to give an answer to any output
e.g. what time of the day is it? will give accurate response as the inputs have been fed every date/time in history till now

EXAMPLE 1

        <> |0.0| <> |0.1| <> |3.5|
|0.3| <><> |2.9| <> |2.5| <> |0.0| <> |2.9|
|1.8| <><> |3.7| <> |3.2| <> |0.4| <> |1.1|
|0.5| <><> |0.0| <> |1.1| <> |3.1| <> |0.0|


EXAMPLE 2

Feeding input's it will through weighting find the right answer

x = "lemon"

= NN(lemon)

= 
|x1|
|x2|
|x3|

=
       <> |0.0| <> |0.1| <> |3.5|
|x1| <><> |2.9| <> |2.5| <> |0.0| <> |apple|
|x2| <><> |3.7| <> |3.2| <> |0.4| <> |oange|
|x3| <><> |0.0| <> |1.1| <> |3.1| <> |I dont know| <----- This is the answer the NN doesn't know what lemons are

The values of the weights are discovered through it's training data set and ask it to produce the correct
outputs and reduce the loss which is the difference between the NN's output function wave and the actual function
wave until it's the same.

Lesson 2 - https://www.youtube.com/watch?v=hjesn5pCEYc
Lesson 3 - https://www.youtube.com/watch?v=kCc8FmEb1nY
Lesson 4 - https://www.youtube.com/watch?v=TsVZJbnnaSs

# TRAINING A NEURAL NETWORK 

To learn A.I. there is a website like Jupyter labs called kaggle here
https://www.kaggle.com/code/dansbecker/your-first-machine-learning-model 
that has interactive lessons, you can also download it's datasets from pip to make things easier.

The excercises below will show importing the data and using various libs to learn.

IMPORT TRAINING DATA
```python
# THIS EXAMPLE REQUIRES MANUALLY DOWNLOADING THIS DATA FILE SET IT'S HERE FOR EXAMPLE ONLY
import pandas as pd
iowa_file_path = '../machine_learning_data_set.csv'
home_data = pd.read_csv(iowa_file_path) # IMPORT TRAINING DATA
print(home_data.describe()) # PRINT STATISTICS

                Id   MSSubClass  LotFrontage        LotArea  OverallQual  \
count  1460.000000  1460.000000  1201.000000    1460.000000  1460.000000   
mean    730.500000    56.897260    70.049958   10516.828082     6.099315   
std     421.610009    42.300571    24.284752    9981.264932     1.382997   
min       1.000000    20.000000    21.000000    1300.000000     1.000000   
25%     365.750000    20.000000    59.000000    7553.500000     5.000000   
50%     730.500000    50.000000    69.000000    9478.500000     6.000000   
75%    1095.250000    70.000000    80.000000   11601.500000     7.000000   
max    1460.000000   190.000000   313.000000  215245.000000    10.000000   

# What is the average lot size (rounded to nearest integer)?
avg_lot_size = 10517

# As of today, how old is the newest home (current year - the date in which it was built)
newest_home_age = 14
```

COMPLETE NEURAL NETWORK EXAMPLE
```python
import pandas as pd
from sklearn.datasets import load_boston
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPRegressor
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error

# Load the Boston housing dataset
boston = load_boston()
X = pd.DataFrame(boston.data, columns=boston.feature_names)
y = pd.Series(boston.target)

# Preprocessing
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# Train-test split
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

# Define and train the model
model = MLPRegressor(hidden_layer_sizes=(50, 50), max_iter=500, random_state=42)
model.fit(X_train, y_train)

# Predict on the test data
predictions = model.predict(X_test)

# Evaluate the model
mse = mean_squared_error(y_test, predictions)
print(f"Mean Squared Error: {mse:.2f}")

# Display a few predictions vs true values
for i in range(5):
    print(f"Predicted: {predictions[i]:.2f}, Actual: {y_test.iloc[i]:.2f}")

```

# CREATING A AI PERSONAL ASSISTANT

To build an AI like Google Home, Siri, Cortana, or Alexa on a home device (called edge hardware)
with the addition of extra features such as computer vision and text output (emailed to you)
you require the below;

HARDWARE REQUIREMENTS
* n100 PC - $300
* Microphone - $100
* Speaker - $100
* Webcam - $100

SOFTWARE REQUIREMENTS
* Speech Recognition Model: Vosk
* LLM: LLAMA

Ensure that the version of CUDA you have is supported by torch. You can find this by running
```bash
PS C:\Users\Sumeet> nvidia-smi
Thu Jul 18 02:37:57 2024
+---------------------------------------------------------------------------------------+
| NVIDIA-SMI 536.99                 Driver Version: 536.99       CUDA Version: 12.2     | <----- CUDA VERSION HERE
|-----------------------------------------+----------------------+----------------------+
| GPU  Name                     TCC/WDDM  | Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp   Perf          Pwr:Usage/Cap |         Memory-Usage | GPU-Util  Compute M. |
|                                         |                      |               MIG M. |
|=========================================+======================+======================|
|   0  NVIDIA GeForce RTX 3060      WDDM  | 00000000:04:00.0  On |                  N/A |
|  0%   38C    P8              16W / 170W |    700MiB / 12288MiB |      3%      Default |
|                                         |                      |                  N/A |
+-----------------------------------------+----------------------+----------------------+

+---------------------------------------------------------------------------------------+
| Processes:                                                                            |
|  GPU   GI   CI        PID   Type   Process name                            GPU Memory |
|        ID   ID                                                             Usage      |
|=======================================================================================|
|    0   N/A  N/A      1832    C+G   C:\Windows\explorer.exe                   N/A      |
|    0   N/A  N/A      1880    C+G   ...tionsPlus\logioptionsplus_agent.exe    N/A      |
|    0   N/A  N/A      2888    C+G   ...Programs\Microsoft VS Code\Code.exe    N/A      |
|    0   N/A  N/A      3860    C+G   ...nt.CBS_cw5n1h2txyewy\SearchHost.exe    N/A      |
|    0   N/A  N/A      8572    C+G   ...2txyewy\StartMenuExperienceHost.exe    N/A      |
|    0   N/A  N/A      8784    C+G   ...siveControlPanel\SystemSettings.exe    N/A      |
|    0   N/A  N/A      8840    C+G   ...oogle\Chrome\Application\chrome.exe    N/A      |
|    0   N/A  N/A      8880    C+G   ...ekyb3d8bbwe\PhoneExperienceHost.exe    N/A      |
|    0   N/A  N/A     10052    C+G   ...mpt_builder\LogiAiPromptBuilder.exe    N/A      |
|    0   N/A  N/A     10604    C+G   ...5n1h2txyewy\ShellExperienceHost.exe    N/A      |
|    0   N/A  N/A     10964    C+G   ...n\126.0.2592.102\msedgewebview2.exe    N/A      |
|    0   N/A  N/A     12124    C+G   ...CBS_cw5n1h2txyewy\TextInputHost.exe    N/A      |
|    0   N/A  N/A     13168    C+G   ...__8wekyb3d8bbwe\WindowsTerminal.exe    N/A      |
+---------------------------------------------------------------------------------------+
```

1. INSTALL LIBS
```bash
# transformers - HuggingFaces library that when used will download the LLM model specified and provide interfacing methods
# torch = pytorch for interfacing and creating LLM's
# asyncio - for asynchrnous you can type chat and the LLM listents for incomming speech/wake words
# sounddevice - for connecting to microphone and speaker hardware on host
# vosk - a speech to text language model
pip3 install transformers torch sounddevice vosk asyncio
```

2. DOWNLOAD VOSK MODEL
```bash
# windows - only for American accents
Invoke-WebRequest -Uri "https://alphacephei.com/vosk/models/vosk-model-small-en-us-0.15.zip" -OutFile "vosk-model-small-en-us-0.15.zip"
Expand-Archive -Path "vosk-model-small-en-us-0.15.zip" -Destination "vosk_speech_model"
Remove-Item -Recurse -Force "vosk-model-small-en-us-0.15.zip"
Move-Item -Path "vosk_speech_model\vosk-model-small-en-us-0.15\*" -Destination "vosk_speech_model"
Remove-Item -Recurse -Force "vosk_speech_model\vosk-model-small-en-us-0.15"

# unix*
curl -O https://alphacephei.com/vosk/models/vosk-model-small-en-us-0.15.zip
unzip vosk-model-small-en-us-0.15.zip
mv vosk-model-small-en-us-0.15 vosk_speech_model
```

3. TRAIN VOSK MODEL
```bash
STEPS HERE - https://alphacephei.com/vosk/models#training-your-own-model
```

6. USING LOCAL LLM
```python
import asyncio
import torch
from transformers import GPT2LMHeadModel, GPT2Tokenizer # LLaMATokenizer, LLaMAForCausalLM
from vosk import Model, KaldiRecognizer
import sounddevice as sd
import json

WAKE_WORDS = ["hi", "hello", "hey", "ai", "hey ai", "hello ai", "hi ai", ]

def detect_wake_word(text):
    for wake_word in WAKE_WORDS:
        if wake_word.lower() in text.lower():
            return True
    return False

def load_model_and_tokenizer(model_name):
    model = GPT2LMHeadModel.from_pretrained(model_name)
    tokenizer = GPT2Tokenizer.from_pretrained(model_name)
    # model = LLaMAForCausalLM.from_pretrained(model_name)
    # tokenizer = LLaMATokenizer.from_pretrained(model_name)
    return model, tokenizer

def generate_response(model, tokenizer, prompt):
    inputs = tokenizer.encode(prompt, return_tensors="pt")
    pad_token_id = tokenizer.eos_token_id
    attention_mask = torch.ones(inputs.shape, dtype=torch.long)  # Create attention mask
    outputs = model.generate(
        inputs,
        attention_mask=attention_mask,  # Pass attention mask
        max_length=150,
        num_return_sequences=1,
        pad_token_id=pad_token_id
    )
    response = tokenizer.decode(outputs[0], skip_special_tokens=True)
    return response

async def recognize_speech(recognizer, model, tokenizer):
    def callback(indata, frames, time, status):
        if recognizer.AcceptWaveform(indata.tobytes()):
            result = recognizer.Result()
            text = json.loads(result).get("text", "")
            if text:
                print(f"You spoke: {text}")
                response = generate_response(model, tokenizer, text)
                print(f"AI: {response}")

    with sd.InputStream(samplerate=16000, channels=1, callback=callback):
        while True:
            await asyncio.sleep(1)

async def handle_text_input(model, tokenizer):
    while True:
        prompt = input("You wrote: ")
        if prompt.lower() in ["exit", "quit"]:
            return
        response = generate_response(model, tokenizer, prompt)
        print(f"AI: {response}")

async def main():
    # Load pre-trained model and tokenizer
    model_name = "gpt2"
    # model_name = "llama-model-name"
    model, tokenizer = load_model_and_tokenizer(model_name)

    # Check device and print information
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

    if device.type == "cuda":
        print(f"CUDA Device Name: {torch.cuda.get_device_name(0)}")
        print(f"CUDA Compute Capability: {torch.cuda.get_device_capability(0)}")
        print(f"CUDA Memory Allocated: {torch.cuda.memory_allocated(0)} bytes")
        print(f"CUDA Memory Cached: {torch.cuda.memory_reserved(0)} bytes")
    else:
        print("No CUDA device found, device: {device}")

    print("Hi I'm Ghar AI. You can ask me any question by typing or talking.")

    # Initialize Vosk model
    model_path = "vosk_speech_model"  # folder that contains the speech model
    try:
        vosk_model = Model(model_path)  # Create Model object from path
        recognizer = KaldiRecognizer(vosk_model, 16000)
        print("Model loaded successfully.")
    except Exception as e:
        print(f"Failed to create a speech model: {e}")
        return

    # Start listening for speech and handling text input concurrently
    await asyncio.gather(
        recognize_speech(recognizer, model, tokenizer),
        handle_text_input(model, tokenizer)
    )

if __name__ == "__main__":
    asyncio.run(main())

```
