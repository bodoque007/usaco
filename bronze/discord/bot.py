import os
import nextcord 
from nextcord.ext import commands
from dotenv import load_dotenv
import requests
import re

load_dotenv()

DISCORD_TOKEN =  os.environ.get('DISCORD_TOKEN')
GEMINI_KEY = os.environ.get('GEMINI_KEY')
GEMINI_URL = f"https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key={GEMINI_KEY}"
NASA_KEY = os.environ.get('NASA_KEY')
NASA_URL = f"https://api.nasa.gov/planetary/apod?api_key={NASA_KEY}"
GUILDS_LIST = [1262172237499334667]

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

bot = commands.Bot()

@bot.event
async def on_ready():
    print(f'We have logged in as {bot.user}')



@bot.slash_command(name="hello", guild_ids=GUILDS_LIST)
async def hello(interaction: nextcord.Interaction):
    await interaction.response.send_message('Hello!')


@bot.slash_command(name="rat", description="Calls out a rat.", guild_ids=GUILDS_LIST)
async def rat(interaction: nextcord.Interaction):
    await interaction.response.send_message('you rat! <@290157213123608576>')


@bot.slash_command(name="ia", description="Message to answer.", guild_ids=GUILDS_LIST)
async def ia(interaction: nextcord.Interaction, message: str):
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
@bot.slash_command(name="apod", guild_ids=GUILDS_LIST)
async def apod(interaction: nextcord.Interaction):

    await interaction.response.defer()
    response = requests.get(NASA_URL)
    json = response.json()
  
    if response.status_code == 200:
        image_content = requests.get(json["url"]).content
        with open("apod.jpg", "wb") as f:
            f.write(image_content)
        await interaction.followup.send(json["explanation"], file=nextcord.File("apod.jpg"))
    else:
        await interaction.followup.send("Non 2xx response :(")



@bot.slash_command(name="reddit", description="Reddit posts.", guild_ids=GUILDS_LIST)
async def reddit(interaction: nextcord.Interaction, subreddit:str ="argentina", category: int = nextcord.SlashOption(
        name="category",
        choices={"top": 1, "new": 2, "all": 3, "rising": 4, "hot": 5},
        default=5
    ), limit:int=5):
    
    categories = ["top", "new", "all", "rising", "hot"]
    selected_category = categories[category - 1]
    limit = min(limit,10)

    await interaction.response.defer()
    response = requests.get(f"https://www.reddit.com/r/{subreddit}/{selected_category}.json?limit={limit}")
    print(f"https://www.reddit.com/r/{subreddit}/{selected_category}.json?limit={limit}")
    json_response = response.json()
    print(json_response)
    embeds = []
    
    posts = json_response["data"]["children"]
    print(posts[0]["data"]["pinned"])
    not_pinned_posts = filter(lambda post: not post["data"]["pinned"], posts)
    print(len(not_pinned_posts))
    if response.status_code == 200:
        for post in not_pinned_posts:
            embed = nextcord.Embed(title=post["data"]["title"], url=post["data"]["url"])
            
            if "url_overridden_by_dest" in post["data"] and re.match(r".*\.(png|jpg|gif)", post["data"]["url_overridden_by_dest"]):
                embed.set_image(url=post["data"]["url_overridden_by_dest"])
            
            elif "thumbnail" in post["data"] and re.match(r".*\.(png|jpg|gif)", post["data"]["thumbnail"]):
                embed.set_image(url=post["data"]["thumbnail"])
            
            embed.set_footer(text=f"Subreddit: {subreddit}")
            embeds.append(embed)
            
        await interaction.followup.send(embeds=embeds)
    else:
        await interaction.followup.send("Non 2xx response :(")


@bot.slash_command(guild_ids=GUILDS_LIST)
async def choose_a_number(
    interaction: nextcord.Interaction,
    number: int = nextcord.SlashOption(
        name="picker",
        choices={"Top": 1, "New": 2, "All": 3},
    ),
):
    """Repeats your number that you choose from a list

    Parameters
    ----------
    interaction: Interaction
        The interaction object
    number: int
        The chosen number.
    """
    await interaction.response.send_message(f"You chose {number}!")



bot.run(DISCORD_TOKEN)

#https://www.youtube.com/watch?v=2lj4XEYQs78