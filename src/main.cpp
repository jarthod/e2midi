#include <iostream>
#include "output_tcp.hpp"
#include "input.hpp"
#include "threshold_trigger.hpp"

int main()
{
  TCPOutput out;
  out.trigger(0.5);

	ThresholdTrigger tt = ThresholdTrigger(out);

	Input in = Input(tt);
	in.run();

	while (1);

  return 0;
}
