#!/usr/bin/python

import socket
import sys
from pygame import mixer

class e2midiClient(object):

    def __init__(self, song_list):
        self.song_list = song_list
        self.song_list.append(song_list[-1])
        print self.song_list
        mixer.init()

    def handle_data(self, position):
        print position
        print "play: %s" % self.song_list[int(position * (len(self.song_list) - 1))]
        sound = mixer.Sound(self.song_list[int(position * (len(self.song_list) - 1))])
        sound.play()

    def listen(self, host):
        s = socket.create_connection((host, 2012))
        data = ""
        while True:
            data += s.recv(255)
            if data.endswith("\n"):
                self.handle_data(float(data))
                data = ""


if __name__ == "__main__":
    client = e2midiClient(sys.argv[2:])
    client.listen(sys.argv[1])
