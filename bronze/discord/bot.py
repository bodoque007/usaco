import os
import discord
from dotenv import load_dotenv
import requests

intents = discord.Intents.default()
intents.message_content = True

load_dotenv()

DISCORD_TOKEN =  os.environ.get('DISCORD_TOKEN')
GEMINI_KEY = os.environ.get('GEMINI_KEY')
GEMINI_URL = f"https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key={GEMINI_KEY}"
NASA_KEY = os.environ.get('NASA_KEY')

NASA_URL = f"https://api.nasa.gov/planetary/apod?api_key={NASA_KEY}"


def build_gemini_request(message):
    headers = {
        "Content-Type": "application/json",
    }

    data = {
        "contents": [
            {
                "parts": [
                    {
                        "text": message
                    }
                ]
            }
        ]
    }

    response = requests.post(
        GEMINI_URL,
        headers=headers,
        json=data
    )
    
    return response


client = discord.Client(intents=intents)

@client.event
async def on_ready():
    print(f'We have logged in as {client.user}')

@client.event
async def on_message(message):
    if message.author == client.user:
        return

    if message.content.startswith('$hello'):
        await message.channel.send('Hello!')
        
    if message.content.startswith('/ia'):
        text = message.content.split()
        text = " ".join(text[1:]) + ". Use at most 400 tokens"
        response = build_gemini_request(text)

        if response.status_code == 200:
            json_response = response.json()
            response = json_response["candidates"][0]["content"]["parts"][0]["text"]
            await message.channel.send(response)
        else:
            await message.channel.send("Non 2xx response")


    if message.content.startswith('/apod'):
        # text = message.content.split()
        # text = " ".join(text[1:])
        response = requests.get(NASA_URL)
        json = response.json()
        
        if response.status_code == 200:
            image_content = requests.get(json["url"]).content
            with open("apod.jpg", "wb") as f:
                f.write(image_content)
            await message.channel.send(json["explanation"], file=discord.File("apod.jpg"))
        else:
            await message.channel.send("Non 2xx response :(")

# Example usage
result = generate_roasts("Your text here")
print(result)

client.run(DISCORD_TOKEN)

#https://www.youtube.com/watch?v=2lj4XEYQs78