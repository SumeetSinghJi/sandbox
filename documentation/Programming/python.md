
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

______________________________________________________________________________________________

                        AI LIKE ROBOTIC ASSISTANT - PYTORCH LLM USING CLOUD API
______________________________________________________________________________________________

LIMITATIONS

* No computer vision as OpenAI key cannot process real time image processing, need dedicated LLM/hardware

If funds are not available to run dedicated LLM on own hardware we can use a speech
to text library + a LLM API such as with a openai account chatgpt 4.0 paid subscription model
with a speech to text python lib such as vosk.

1. In OpenAI create an account and subscribe to latest GPT model.
You will then get access to API which is roughly $10 for ~2800 questions/answers tokens
Make an API key and store it as an environmental variable
```bash
export OPENAI_API_KEY='your_openai_api_key' # unix
$env:OPENAI_API_KEY='your_openai_api_key' # windows
```

2. (OPTIONAL) On OpenAI portal set token limit

3. INSTALL LIBS ON HOST DEVICE e.g. PI
```bash
pip3 install torch transformers vosk sounddevice
```

4. DOWNLOAD VOSK MODEL
```bash
# windows
Invoke-WebRequest -Uri "https://alphacephei.com/vosk/models/vosk-model-small-en-us-0.15.zip" -OutFile "vosk-model-small-en-us-0.15.zip"
Expand-Archive -Path "vosk-model-small-en-us-0.15.zip" -DestinationPath "vosk-model-small-en-us-0.15"
Rename-Item -Path "vosk-model-small-en-us-0.15" -NewName "model"

# unix*
wget https://alphacephei.com/vosk/models/vosk-model-small-en-us-0.15.zip
unzip vosk-model-small-en-us-0.15.zip
mv vosk-model-small-en-us-0.15 model
```

5. CREATE SCRIPT 'gpt4_api.py' REPLACING OPENAI_KEY
```python
# gpt_api.py
import os
import queue
import sounddevice as sd
import vosk
import sys
import json
import openai
import pyttsx3
import time

# Initialize OpenAI API using environment variable
openai.api_key = os.getenv('OPENAI_API_KEY')

# Initialize text-to-speech
engine = pyttsx3.init()

# Initialize Vosk model
model_path = "model"
if not os.path.exists(model_path):
    print(f"Please download the model from https://alphacephei.com/vosk/models and unpack as '{model_path}'")
    sys.exit(1)

model = vosk.Model(model_path)
q = queue.Queue()

# Usage limits
daily_token_limit = 1500  # Adjust based on your needs
monthly_token_limit = 45000  # Adjust based on your needs
daily_tokens_used = 0
monthly_tokens_used = 0
start_of_month = time.time()

def reset_daily_counter():
    global daily_tokens_used
    daily_tokens_used = 0

def reset_monthly_counter():
    global monthly_tokens_used
    monthly_tokens_used = 0

def check_and_update_limits(tokens):
    global daily_tokens_used, monthly_tokens_used

    current_time = time.time()
    time_since_month_start = current_time - start_of_month

    # Reset monthly counter if it's a new month
    if time_since_month_start >= 30 * 24 * 60 * 60:  # 30 days
        reset_monthly_counter()

    # Reset daily counter if it's a new day
    if time.localtime(current_time).tm_mday != time.localtime(current_time - 24 * 60 * 60).tm_mday:
        reset_daily_counter()

    # Check if limits are reached
    if daily_tokens_used + tokens > daily_token_limit:
        print("Daily token limit reached. Please try again tomorrow.")
        return False
    if monthly_tokens_used + tokens > monthly_token_limit:
        print("Monthly token limit reached. Please try again next month.")
        return False

    # Update counters
    daily_tokens_used += tokens
    monthly_tokens_used += tokens
    return True

def get_tokens_used(response):
    return response['usage']['total_tokens']

def recognize_speech_callback(indata, frames, time, status):
    if status:
        print(status, file=sys.stderr)
    q.put(bytes(indata))

def chat_with_gpt(prompt):
    response = openai.Completion.create(
        engine="text-davinci-003",
        prompt=prompt,
        max_tokens=150
    )
    tokens_used = get_tokens_used(response)
    if check_and_update_limits(tokens_used):
        return response.choices[0].text.strip()
    return None

def speak_text(text):
    engine.say(text)
    engine.runAndWait()

def main():
    with sd.RawInputStream(samplerate=16000, blocksize=8000, dtype='int16',
                           channels=1, callback=recognize_speech_callback):
        print('#' * 80)
        print('Press Ctrl+C to stop the recording')
        print('#' * 80)

        rec = vosk.KaldiRecognizer(model, 16000)
        while True:
            data = q.get()
            if rec.AcceptWaveform(data):
                result = rec.Result()
                result_dict = json.loads(result)
                text = result_dict.get('text', '')
                if text:
                    print("You said:", text)
                    gpt_response = chat_with_gpt(text)
                    if gpt_response:
                        print("ChatGPT says:", gpt_response)
                        speak_text(gpt_response)

if __name__ == "__main__":
    main()
```

6. CONNECT HARDWARE PERIPHERALS MIC AND SPEAKER

7. RUN THEN TEST
```bash
main.py

>>> What is the temprature today?
```

______________________________________________________________________________________________

                                    AI - PYTORCH LLM ON DEDICATED HARDWARE
______________________________________________________________________________________________


Below steps outline using pytorch with huggingfaces transformers library to create a context
with any LLM model from here: https://huggingface.co/models

Then once run it will download and save/cache the LLM model e.g. GPT2.0 on your computer.
So even if you quit the terminal AI interactive prompt session you can interact
with either CLI or use voice which will be converted to text with the vosk library.
for next time


PREREQUISITES

Pytorch (and it's library known as torch) only works with Nvidia's GPU - CUDA langauge, by default. 
If it doesn't detect a available CUDA version on the host from the GPU to work with it will 
default to using the CPU to run tasks.

If you have a none Nvidia GPU such as an AMD GPU which uses it's own language e.g. OpenCL, then
you would need to load/import it's library and then configure torch to use it, the same way
when designing a c++ game you would import OpenGL libraries to create contexts with the GPU
so that you can send images/textures for rendering.

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
# transformers it HuggingFaces library that when used will download the LLM model specified
# torch = pytorch for interfacing and creating LLM's
# asyncio - for asynchrnous you can type chat and the LLM listents for incomming speech/wake words
# sounddevice - for connecting to microphone and speaker hardware on host
# vosk - a speech to text language model
pip3 install transformers torch sounddevice vosk asyncio
```

2. DOWNLOAD VOSK MODEL
```bash
# windows - lightweight American language 55MB+ model size
Invoke-WebRequest -Uri "https://alphacephei.com/vosk/models/vosk-model-small-en-us-0.15.zip" -OutFile "vosk-model-small-en-us-0.15.zip"
Expand-Archive -Path "vosk-model-small-en-us-0.15.zip" -Destination "vosk_speech_model"
Remove-Item -Recurse -Force "vosk-model-small-en-us-0.15.zip"
Move-Item -Path "vosk_speech_model\vosk-model-small-en-us-0.15\*" -Destination "vosk_speech_model"
Remove-Item -Recurse -Force "vosk_speech_model\vosk-model-small-en-us-0.15"

# windows - alternate for Australian accents using comprehensive 1.8gb+ model size - Best to manually download using browser
Invoke-WebRequest -Uri "https://alphacephei.com/vosk/models/vosk-model-en-us-0.22.zip" -OutFile "vosk-model-en-us-0.22.zip"
Expand-Archive -Path "vosk-model-en-us-0.22.zip" -Destination "vosk_speech_model"
Remove-Item -Recurse -Force "vosk-model-en-us-0.22.zip"
Move-Item -Path "vosk_speech_model\vosk-model-en-us-0.22\*" -Destination "vosk_speech_model"
Remove-Item -Recurse -Force "vosk_speech_model\vosk-model-en-us-0.22"

# unix*
wget https://alphacephei.com/vosk/models/vosk-model-small-en-us-0.15.zip
unzip vosk-model-small-en-us-0.15.zip
mv vosk-model-small-en-us-0.15 vosk_speech_model
rm vosk-model-small-en-us-0.15.zip
mv vosk_speech_model/vosk-model-small-en-us-0.15/* vosk_speech_model
rmdir vosk_speech_model/vosk-model-small-en-us-0.15
```

3. CREATE SCRIPT TO DOWNLOAD REQUIRED EDGE LLM MODEL AND START
```python
import torch
from transformers import GPT2LMHeadModel, GPT2Tokenizer
from vosk import Model, KaldiRecognizer
import sounddevice as sd
import numpy as np
import json

WAKE_WORDS = ["hey", "hello", "Hi"]

def detect_wake_word(text):
    for wake_word in WAKE_WORDS:
        if wake_word.lower() in text.lower():
            return True
    return False

def load_model_and_tokenizer(model_name):
    model = GPT2LMHeadModel.from_pretrained(model_name)
    tokenizer = GPT2Tokenizer.from_pretrained(model_name)
    return model, tokenizer

def generate_response(model, tokenizer, prompt):
    inputs = tokenizer.encode(prompt, return_tensors="pt")
    attention_mask = torch.ones(inputs.shape, dtype=torch.long)  # Create an attention mask
    pad_token_id = tokenizer.eos_token_id
    outputs = model.generate(
        inputs, 
        attention_mask=attention_mask,
        max_length=150, 
        num_return_sequences=1, 
        pad_token_id=pad_token_id
    )
    response = tokenizer.decode(outputs[0], skip_special_tokens=True)
    return response

def recognize_speech(recognizer, model, tokenizer, duration=5, fs=16000):
    print("Listening...")

    def callback(indata, frames, time, status):
        if recognizer.AcceptWaveform(indata.tobytes()):
            result = recognizer.Result()
            text = json.loads(result).get("text", "")
            if text:
                print(f"You (speech): {text}")
                response = generate_response(model, tokenizer, text)
                print(f"AI: {response}")

    with sd.InputStream(samplerate=fs, channels=1, callback=callback):
        sd.sleep(int(duration * 1000))

if __name__ == "__main__":
    # Load pre-trained model and tokenizer
    model_name = "gpt2"
    model, tokenizer = load_model_and_tokenizer(model_name)

    # Check device and print information
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print(f"Using device: {device}")

    if device.type == "cuda":
        print(f"CUDA Device Name: {torch.cuda.get_device_name(0)}")
        print(f"CUDA Compute Capability: {torch.cuda.get_device_capability(0)}")
        print(f"CUDA Memory Allocated: {torch.cuda.memory_allocated(0)} bytes")
        print(f"CUDA Memory Cached: {torch.cuda.memory_reserved(0)} bytes")
    else:
        print("No CUDA device found, using CPU.")

    print("Hi I'm Ghar AI. You can ask me any question by typing or talking.")

    # Initialize Vosk model
    vosk_model = Model("model")
    recognizer = KaldiRecognizer(vosk_model, 16000)

    while True:
        mode = input("Type 'text' to type a question or 'speech' to talk to the AI: ").strip().lower()
        if mode == "exit" or mode == "quit":
            break
        elif mode == "text":
            prompt = input("You: ")
            response = generate_response(model, tokenizer, prompt)
            print(f"AI: {response}")
        elif mode == "speech":
            print("Waiting for wake word...")
            while True:
                with sd.InputStream(samplerate=16000, channels=1) as stream:
                    sd.sleep(1000)
                    print("Listening...")
                    audio_input = stream.read(16000 * 5)[0]  # Record 5 seconds of audio
                    recognizer.SetWords(True)
                    if recognizer.AcceptWaveform(audio_input.tobytes()):
                        result = json.loads(recognizer.Result())
                        text = result["text"]
                        if detect_wake_word(text):
                            print(f"Wake word detected: {text}")
                            recognize_speech(recognizer, model, tokenizer)
                            break
                        else:
                            print(f"Detected: {text}")
                    else:
                        print("Failed to recognize speech.")
        else:
            print("Invalid mode. Please type 'text' or 'speech'.")
```