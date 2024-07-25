
______________________________________________________________________________________________

                                     WHAT IS AI
______________________________________________________________________________________________

Watch here - https://www.youtube.com/watch?v=TkwXa7Cvfr8 


A neural network can be viewed as a function f(x)≈NN(x) that maps inputs (x) to outputs (y) through a series of transformations. This function is learned from training data.

An example is using pandas to import some data such as housing prices this year in Sydney, Australia, using
huggingfaces transformation library to connect to an LLM such as ChatGPT which is the neural network, 
and then use pytorch's torch import library to connect to the LLM and find predictions.

When you download a LLM such as with using huggingfaces simple code to import, then the LLM's such as ChatGPT2
already come with their weights as part of the file size. You can feed it more data if you wish, or use as is
to answer questions which is called Natural Language Processing (NLP). Using the existing trained LLM this way
is called inference which means using a LLM model after it's been trained.



A Neural network NN(x)

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


______________________________________________________________________________________________

             EXAMPLE IMPORT TRAINING DATA AND USING NEURAL NETWORK TO ANSWER 
______________________________________________________________________________________________

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


______________________________________________________________________________________________

                COMPLETE VOICE ACTIVATED EDGE HARDWARE LLM SETUP STEPS
______________________________________________________________________________________________

To build an AI like Google Home, Siri, Cortana, or Alexa on a home device (called edge hardware)
with the addition of extra features such as computer vision and text output (emailed to you)
you require the below;

HARDWARE REQUIREMENTS
* Raspberry Pi 5 - $140
* Pi 5 PSU - $20
* Pi 5 UPS/portable battery - $150
* Geekworm NVMe dual m.2 hat - $50
* Hailo 8 - 10 - $300 - 500
* 1TB NVMe m.2 - $100
* Microphone - $50
* Speaker - $50
* Pi 5 Module 3 camera wide - $50

SOFTWARE REQUIREMENTS
* Speech Recognition Model: Vosk
* LLM: LLAMA

Alternatively, there is an option to use the ChatGPT API (but that is not private and cannot perform computer vision). Trying to send 100 images a second using the ChatGPT API could be extremely costly and would require the fastest internet possible.

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

4. CONNECT PERIPHERALS TO EDGE HARDWARE

5. (OPTIONAL- CLOUD) USING GOOGLE SPEECH TO TEXT - CHAT GPT API - GOOGLE TEXT TO SPEECH
```bash
export OPENAI_API_KEY='your_openai_api_key' # unix
$env:OPENAI_API_KEY='your_openai_api_key' # windows
```
```python
# gpt_api.py
import os
import io
import sys
import asyncio
import argparse
import pyaudio
import wave
from google.cloud import speech
from google.cloud import texttospeech
from ChatGPT_lite.ChatGPT import Chatbot


gpt_response = ""


def speech_to_text(speech_file):
    client = speech.SpeechClient()

    with io.open(speech_file, "rb") as audio_file:
            content = audio_file.read()

    audio = speech.RecognitionAudio(content=content)

    config = speech.RecognitionConfig(
        encoding=speech.RecognitionConfig.AudioEncoding.LINEAR16,
        language_code="en-US",
    )

    # Detects speech in the audio file
    response = client.recognize(config=config, audio=audio)

    stt = ""
    for result in response.results:
        stt += result.alternatives[0].transcript

    return stt


def ask_chat_gpt(args, prompt):
    global gpt_response
    chat = Chatbot(args.session_token, args.bypass_node)
    
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    loop.run_until_complete(chat.wait_for_ready())
    response = loop.run_until_complete(chat.ask(prompt))
    chat.close()
    loop.stop()
    
    gpt_response = response['answer']

    return


def text_to_speech(tts):
    # Instantiates a client
    client = texttospeech.TextToSpeechClient()

    # Set the text input to be synthesized
    synthesis_input = texttospeech.SynthesisInput(text=tts)

    # Build the voice request, select the language code ("en-US") and the ssml
    voice = texttospeech.VoiceSelectionParams(
        language_code="en-US", ssml_gender=texttospeech.SsmlVoiceGender.FEMALE
    )

    # Select the type of audio file you want returned
    audio_config = texttospeech.AudioConfig(
        audio_encoding=texttospeech.AudioEncoding.LINEAR16
    )

    # Perform the text-to-speech request on the text input with the selected
    # voice parameters and audio file type
    response = client.synthesize_speech(
        input=synthesis_input, voice=voice, audio_config=audio_config
    )

    # The response's audio_content is binary.
    with open("result.wav", "wb") as out:
        # Write the response to the output file.
        out.write(response.audio_content)

    return


def record_wav():
    form_1 = pyaudio.paInt16
    chans = 1
    samp_rate = 16000
    chunk = 4096
    record_secs = 3
    dev_index = 1
    wav_output_filename = 'input.wav'

    audio = pyaudio.PyAudio()

    # Create pyaudio stream.
    stream = audio.open(format = form_1,rate = samp_rate,channels = chans, \
                        input_device_index = dev_index,input = True, \
                        frames_per_buffer=chunk)
    print("recording")
    frames = []

    # Loop through stream and append audio chunks to frame array.
    for ii in range(0,int((samp_rate/chunk)*record_secs)):
        data = stream.read(chunk)
        frames.append(data)

    print("finished recording")

    # Stop the stream, close it, and terminate the pyaudio instantiation.
    stream.stop_stream()
    stream.close()
    audio.terminate()

    # Save the audio frames as .wav file.
    wavefile = wave.open(wav_output_filename,'wb')
    wavefile.setnchannels(chans)
    wavefile.setsampwidth(audio.get_sample_size(form_1))
    wavefile.setframerate(samp_rate)
    wavefile.writeframes(b''.join(frames))
    wavefile.close()

    return


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--session_token_file', type=str, default="openai_session.txt")
    parser.add_argument('--bypass_node', type=str, default="https://gpt.pawan.krd")
    args = parser.parse_args()

    # Get OpenAI credentials from file.
    text_file = open(args.session_token_file, "r")
    args.session_token = text_file.read()
    text_file.close()

    # Get WAV from microphone.
    record_wav()

    # Convert audio into text.
    question = speech_to_text("input.wav")
    
    # Send text to ChatGPT.
    print("Asking: {0}".format(question))
    asyncio.coroutine(ask_chat_gpt(args, question))
    print("Response: {0}".format(gpt_response))

    # Convert ChatGPT response into audio.
    text_to_speech(gpt_response)

    # Play audio of reponse.
    os.system("aplay result.wav")


if __name__ == "__main__":
    main()
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
