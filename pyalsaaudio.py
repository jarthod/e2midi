#!/usr/bin/python

import alsaaudio

p_play = alsaaudio.PCM(alsaaudio.PCM_PLAYBACK, alsaaudio.PCM_NORMAL)
p_record = alsaaudio.PCM(alsaaudio.PCM_CAPTURE, alsaaudio.PCM_NORMAL)

while True:
    (size, data) = p_record.read()
    if size > 0:
         p_play.write(data)
