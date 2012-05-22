Everything to MIDI
==================

This project is a *hack* made during the [Music Hack Paris](http://www.musichackparis.org/) on April 20-22, 2012 by [Adrien Jarthon](https://github.com/jarthod), [Jocelyn De La Rosa](https://github.com/dreewoo) and [Maxime Mouial](https://github.com/hush-hush)

It's a C++ software able to detect sound (like finger snap, hand clap or tap) and localize them in space using 2 microphones. Then, depending on the position, the software can trigger different MIDI output.

It is build in C++ and supports very simple MIDI output and TCP Socket output.
We also provide a Python TCP client to play audio sample, and one to display GUI debug.

Requirements
------------

You need:
- 2 Microphones (they have to be identical and distant, we used our HP Envy 14's build in stereo mic)
- Linux, G++ and Make
- libstk (Ubuntu: `$ sudo apt-get install stk libstk0-dev`)

![HP Envy 14 stereo Mic](http://photo.rootbox.fr/files/13051_large.jpg)

How to run
----------

    $ make
    $ ./e2midi

The software will start listening on the default audio input and open a TCP port (default behaviour). You can change output type by editing `main.cpp`.

![Terminal running e2midi](http://photo.rootbox.fr/files/13052_large.jpg)

Python client
-------------

TODO