#ifndef INPUT_HPP

#define INPUT_HPP

#include "RtAudio.h"
#include "trigger.hpp"

class Input {
public:
  Input(Trigger& trgr);
  void run();
  void close();
protected:
private:
  Trigger &trigger;
  RtAudio dac;
};

#endif //INPUT_HPP
