from vosk import Model, KaldiRecognizer
import sounddevice as sd
import json

def callback(indata, frames, time, status):
    if status:
        print(status, flush=True)
    if recognizer.AcceptWaveform(indata.tobytes()):
        result = recognizer.Result()
        text = json.loads(result).get("text", "")
        if text:
            print(f"Detected Speech: {text}")

def main():
    # Initialize Vosk model
    model_path = "vosk_speech_model"  # Update this path to your Vosk model directory
    try:
        vosk_model = Model(model_path)  # Create Model object from path
        global recognizer
        recognizer = KaldiRecognizer(vosk_model, 16000)
        print("Model loaded successfully.")
    except Exception as e:
        print(f"Failed to create a model: {e}")
        return

    # Start the audio input stream
    with sd.InputStream(samplerate=16000, channels=1, callback=callback):
        print("Listening...")
        sd.sleep(10000)  # Listen for 10 seconds

if __name__ == "__main__":
    main()
