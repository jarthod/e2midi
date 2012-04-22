#!/usr/bin/python

import socket
import sys
from pygame import mixer

class e2midiClient(object):

    def __init__(self, song_list):
        self.sound = []
        mixer.init()
        for i in song_list:
            self.sound.append(mixer.Sound(i))

    def handle_data(self, position):
        print position
        print "play: %s" % int(position * len(self.sound))
        self.sound[min(len(self.sound) - 1, int(position * len(self.sound)))].play()

    def listen(self, host):
        s = socket.create_connection((host, 2012))
        data = ""
        while True:
            data += s.recv(255)
            if data.endswith("\n"):
                [self.handle_data(float(nb)) for nb in data.split('\n') if nb != '']
                data = ""


if __name__ == "__main__":
    client = e2midiClient(sys.argv[2:])
    client.listen(sys.argv[1])
