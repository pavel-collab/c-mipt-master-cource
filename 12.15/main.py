from vllm import LLM, SamplingParams
import torch

#! chose some llm
model_name = 'unsloth/Qwen2.5-Coder-32B-Instruct-128K-GGUF'

if "bnb-4bit" in model_name:
    llm = LLM(model=model_name, 
            max_model_len=4096, 
            trust_remote_code=True,
            dtype=torch.bfloat16, #! exchange to the sutable tensor type 
            quantization="bitsandbytes", 
            load_format="bitsandbytes")
else:
    llm = LLM(model=model_name, 
            max_model_len=4096, 
            trust_remote_code=True)
    
sampling_params = SamplingParams(temperature=0.9, 
                                 top_p=0.9, 
                                 max_tokens=512, #! check, how many tokens we can store in history 
                                 n=1)

user_prompt = "Write a text. Text should contain 25 scentences. Each scentence should contain correct email addresses or incorrect email addresses. As a result text have to contain 15 correct email addresses and 10 incorrect email addresses."

input_code = input() # ожидаем на вход исходный код

prompt = user_prompt.format(code=input_code)

conversation = [
    {"role": "system",
    "content": "You are a tester in IT company."},
    
    {"role": "user",
    "content": prompt}
]

outputs = llm.chat(conversation,
                   sampling_params=sampling_params,
                   use_tqdm=False)

for output in outputs:
    for out in output.outputs:
        print(out.text)