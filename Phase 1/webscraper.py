# web scraper to get the champion pics from internet
import re

import requests
from bs4 import BeautifulSoup
import os

url = "https://leagueoflegends.fandom.com/wiki/List_of_champions"
page = requests.get(url)
soup = BeautifulSoup(page.content, 'html.parser')
# find thread in html
thread = soup.find('table', class_='article-table')
print(thread)
# find all the links in the thread with href like /wiki/___/LoL
href = re.findall(r'href="\/wiki\/[a-zA-Z0-9_]+\/LoL"', str(thread))

# GO THROUGH EACH LINK AND GET THE IMAGE
for link in href:
    # get the name of the champion
    champion = re.findall(r'\/wiki\/[a-zA-Z0-9_]+\/LoL', link)[0]
    champion = champion[6:-4]
    # get the url of the champion
    url = "https://leagueoflegends.fandom.com" + link[6:-1]
    # get the page of the champion
    page = requests.get(url)
    soup = BeautifulSoup(page.content, 'html.parser')
    # find the image of the champion
    image = soup.find('img', class_='pi-image-thumbnail')
    # get the url of the image
    image_url = image['src']
    # get the image
    image = requests.get(image_url, stream=True)
    # save the image
    path = "./champion/" + champion + ".png"
    with open(path, 'wb') as f:
        for chunk in image:
            f.write(chunk)
    print(champion)

