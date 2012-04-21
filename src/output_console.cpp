#include "output_console.hpp"
#include <iostream>

void  ConsoleOutput::trigger(float p) {
  std::cout << "ConsoleOutput trigger: " << p << std::endl;
}