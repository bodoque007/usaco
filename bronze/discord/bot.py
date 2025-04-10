import os
import discord
from discord.ext import commands
from discord import app_commands
from dotenv import load_dotenv
import requests

load_dotenv()

DISCORD_TOKEN =  os.environ.get('DISCORD_TOKEN')
GEMINI_KEY = os.environ.get('GEMINI_KEY')
GEMINI_URL = f"https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key={GEMINI_KEY}"
NASA_KEY = os.environ.get('NASA_KEY')
NASA_URL = f"https://api.nasa.gov/planetary/apod?api_key={NASA_KEY}"
GUILD_ID = discord.Object(id=1262172237499334667)

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

intents = discord.Intents.default()
intents.message_content = True
bot = commands.Bot(command_prefix="c!", intents=discord.Intents.all())
GUILD_ID = discord.Object(id=1262172237499334667)


@bot.event
async def on_ready():
    print(f'We have logged in as {bot.user}')
    try:
        synced = await bot.tree.sync()
        print(f'Synced {len(synced)} command(s).')
    except Exception as e:
        print(f"Error syncing commands: {e}")

#https://stackoverflow.com/questions/77447813/issues-with-the-discord-api-unknown-interaction-discord-js


@bot.tree.command(name="hello")
async def hello(interaction: discord.Interaction):
    await interaction.response.send_message('Hello!')

@bot.tree.command(name="ia")
@app_commands.describe(message="Message to answer.")
async def ia(interaction: discord.Interaction, message: str):
    await interaction.response.defer()  # Acknowledge the interaction
    print(interaction)
    text = message.split()
    text = " ".join(text[1:]) + ". Use at most 400 tokens."
    response = build_gemini_request(text)

    if response.status_code == 200:
        json_response = response.json()
        response_text = json_response["candidates"][0]["content"]["parts"][0]["text"]
        await interaction.followup.send(response_text)  # Send the response later
    else:
        await interaction.followup.send("Non 2xx response")
      

# https://www.youtube.com/watch?v=jh1CtQW4DTo
@bot.tree.command(name="apod")
async def apod(interaction: discord.Interaction):

    await interaction.response.defer()
    response = requests.get(NASA_URL)
    json = response.json()
  
    if response.status_code == 200:
        image_content = requests.get(json["url"]).content
        with open("apod.jpg", "wb") as f:
            f.write(image_content)
        await interaction.followup.send(json["explanation"], file=discord.File("apod.jpg"))
    else:
        await interaction.followup.send("Non 2xx response :(")


bot.run(DISCORD_TOKEN)

#https://www.youtube.com/watch?v=2lj4XEYQs78