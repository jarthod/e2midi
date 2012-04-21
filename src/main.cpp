#include <iostream>
#include "output_console.hpp"
#include "input.hpp"
#include "threshold_trigger.hpp"

int main()
{
  ConsoleOutput out;
  out.trigger(0.5);

	ThresholfTrigger tt = ThresholfTrigger(out);

	Input in = Input(tt);
	in.run();

	while (1);

  return 0;
}
