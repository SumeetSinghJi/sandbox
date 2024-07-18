# ./gpt_llm.py

import torch # pytorch
from transformers import GPT2LMHeadModel, GPT2Tokenizer # huggingface downloads LLM here C:\Users\Sumeet\.cache\huggingface\
from vosk import Model, KaldiRecognizer # speech to text lib
import sounddevice as sd # lib to access host sound/mic hardware
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
    pad_token_id = tokenizer.eos_token_id  # Define pad token id
    outputs = model.generate(inputs, max_length=150, num_return_sequences=1, pad_token_id=pad_token_id)
    response = tokenizer.decode(outputs[0], skip_special_tokens=True)
    return response

def recognize_speech(recognizer, model, tokenizer, duration=5, fs=16000):
    print("Listening...")

    def callback(indata, frames, time, status):
        if recognizer.AcceptWaveform(indata):
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
                    audio_input = stream.read(16000 * 5)  # Record 5 seconds of audio
                    recognizer.SetWords(True)
                    if recognizer.AcceptWaveform(audio_input):
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
