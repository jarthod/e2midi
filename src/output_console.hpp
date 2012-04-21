#ifndef OUTPUT_CONSOLE_HPP
#define OUTPUT_CONSOLE_HPP

#include "output.hpp"

class ConsoleOutput : public Output {
public:
  void    trigger(float p);
};

#endif