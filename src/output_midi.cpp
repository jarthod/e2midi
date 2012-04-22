#include "output_midi.hpp"
#include <iostream>

MidiOutput::MidiOutput() : midi("e2midi")
{
  midi.openPort();
  std::cout << "MidiOutput port: " << midi.getPortName() << std::endl;
}

void  MidiOutput::trigger(float p)
{
  int n = p * 3;
  std::cout << "MidiOutput trigger: " << p << std::endl;
  std::vector<unsigned char> on = std::vector<unsigned char>();
  on.push_back(0x90);
  on.push_back(0x48 + n);
  on.push_back(0x10);
  midi.sendMessage(&on);

//  std::vector<unsigned char> off = std::vector<unsigned char>();
//  off.push_back(0x80);
//  off.push_back(0x48);
//  off.push_back(0x10);
}