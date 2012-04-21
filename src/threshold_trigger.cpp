#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "threshold_trigger.hpp"

ThresholfTrigger::ThresholfTrigger(Output& output)
: Trigger(output), output(output)
{}

void ThresholfTrigger::feedMe(stk::StkFloat *samples, unsigned int buffSize)
{
	int left_start = -1;
	int right_start = -1;

	std::cout << "new frame" << std::endl;
	for (unsigned int i = 0; i < buffSize; i += 2)
	{
		if (abs(samples[i]) > THRESHOLD)
			left_start = i;
		if (abs(samples[i + 1]) > THRESHOLD)
			right_start = i + 1;
		if (left_start >= 0 && right_start >= 0)
		{
			std::cout << "trigger !" << std::endl;
			this->output.trigger(std::max(0, std::min(1, ((left_start - right_start + 10) / 20))));
			return;
		}
	}
}
