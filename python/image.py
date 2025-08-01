from openai import OpenAI
import base64, os
client = OpenAI(
  api_key=os.getenv("OPENAI_API_KEY")
)

prompt = input("what image u want?: ")

result = client.images.generate(
  model="dall-e-3",
  prompt=prompt,
  response_format="b64_json"
)

image_base64 = result.data[0].b64_json
image_bytes = base64.b64decode(image_base64)

# Save the image to a file
with open(f"{prompt.replace(" ", "")}.png", "wb") as f:
  f.write(image_bytes)