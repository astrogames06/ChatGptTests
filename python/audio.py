from openai import OpenAI
import os
client = OpenAI(
  api_key=os.getenv("OPENAI_API_KEY")
)

audio_file = open("voice.mp3","rb")

transcript = client.audio.transcriptions.create(model="whisper-1", file=audio_file)

print(transcript.text)