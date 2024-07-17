# ./gpt2_question_answering.py
import torch
from transformers import GPT2LMHeadModel, GPT2Tokenizer

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

    # Example usage
    prompt = "What's the temperature in Sydney Australia?"
    response = generate_response(model, tokenizer, prompt)
    print("AI:", response)

    # Interactive mode
    while True:
        prompt = input("You: ")
        if prompt.lower() in ["exit", "quit"]:
            break
        response = generate_response(model, tokenizer, prompt)
        print("AI:", response)
