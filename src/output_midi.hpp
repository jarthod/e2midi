#ifndef OUTPUT_MIDI_HPP
#define OUTPUT_MIDI_HPP

#include <RtMidi.h>
#include "output.hpp"

class MidiOutput : public Output {
public:
  MidiOutput();
  void    trigger(float p);

private:
  RtMidiOut midi;  
};

#endif