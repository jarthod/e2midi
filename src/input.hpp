#ifndef INPUT_HPP

#define INPUT_HPP

#include "RtAudio.h"

class Input {
public:
  Input();
  void run();
  void close();
protected:
private:
  Triger &triger;
  RtAudio dac;
};

#endif //INPUT_HPP
