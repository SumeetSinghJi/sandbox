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
