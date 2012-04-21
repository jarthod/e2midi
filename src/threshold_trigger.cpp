#include <cstdlib>
#include "threshold_trigger.hpp"

ThresholfTrigger::ThresholfTrigger(Output& output)
: output(output)
{}

void ThresholfTrigger::feedMe(StkFloat *samples, unsigned int buffSize)
{
	unsigned int left_start = -1;
	unsigned int right_start = -1;

	for (int i = 0; i < buffSize; i += 2)
	{
		if (abs(samples[i]) > THRESHOLD)
			left_start = i
		if (abs(samples[i + 1]) > THRESHOLD)
			right_start = i + 1;
		if (left_start >= 0 && right_start >= 0)
		{
			this->output->trigger(max(0, min(1, ((left_start - right_start + 10) / 20))));
			return;
		}
	}
}
