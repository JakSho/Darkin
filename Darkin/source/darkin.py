import keyboard
import pandas as pd
import numpy as np
import json
import os
import sys
import time
import requests
import psutil

class Darkin:
    def __init__(self, data):
        self.darkin = data

    def __str__(self):
        s = ""
        for key in self.darkin:
            s += key + ": " + "\n"
            # see if iterable
            try:
                for k in self.darkin[key]:
                    try:
                        for i in self.darkin[key][k]:
                            s += "\t\t" + i + ": " + str(self.darkin[key][k][i]) + "\n"
                    except TypeError:
                        s += "\t" + k + ": " + str(self.darkin[key][k]) + "\n"
            except TypeError:
                s += "\t" + str(self.darkin[key]) + "\n"

        return s


def load_darkin(timestamp):
    path = "../resource/darkin"+timestamp+".json"
    if os.path.exists(path):
        with open(path, 'r') as f:
            data = json.load(f)
        return data
    else:
        return None


def refresh_darkin():
    url = 'https://127.0.0.1:2999/liveclientdata/allgamedata'
    r = requests.get(url, verify=False)
    data = r.json()
    timestamp = str(time.time())
    path = "../resource/darkin"+timestamp+".json"
    with open(path, 'w') as outfile:
        json.dump(data, outfile)
    return data

def process_exists():
    process = "League of Legends.exe"
    for proc in psutil.process_iter():
        if proc.name() == process:
            return True


def to_Darkin(data):
    darkin = Darkin(data['activePlayer'])
    print(darkin)





