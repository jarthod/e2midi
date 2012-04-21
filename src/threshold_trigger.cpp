#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <math.h>
#include "threshold_trigger.hpp"

const stk::StkFloat ThresholdTrigger::WIDTH = 10;
const double ThresholdTrigger::THRESHOLD = 2;

ThresholdTrigger::ThresholdTrigger(Output& output)
: Trigger(output), output(output)
{}

void ThresholdTrigger::feedMe(stk::StkFloat *samples, unsigned int buffSize)
{
	const int avg_width = 80;
	stk::StkFloat lavg = 0, ravg = 0;
	int left_start = -1;
	int right_start = -1;
	std::stringstream	out;

	for (unsigned int i = 0; i < buffSize * 2; i += 2)
	{
		lavg += fabs(samples[i]);// * samples[i];
		ravg += fabs(samples[i + 1]);// * samples[i + 1];
		if (i >= avg_width * 2) {
			lavg -= fabs(samples[i - avg_width * 2]);// * samples[i - avg_width * 2];
			ravg -= fabs(samples[i + 1 - avg_width * 2]);// * samples[i + 1 - avg_width * 2];
		}
		if (((i/2) - left_start) > (WIDTH * 2))
			left_start = -1;
		if (((i/2) - right_start) > (WIDTH * 2))
			right_start = -1;
		if ((left_start < 0) && (lavg > THRESHOLD))
			left_start = i / 2;
		if ((right_start < 0) && (ravg > THRESHOLD))
			right_start = i / 2;
		//out << "[" << i << "] " << samples[i] << "," << samples[i+1] << "," << lavg << "," << ravg << "," << left_start << "," << right_start << std::endl;  
		if (left_start >= 0 && right_start >= 0)
		{
			//std::cerr << out.rdbuf();
			//out.clear();
			std::cout << "trigger ! " << lavg << " - " << ravg << " - " << left_start << " - " << right_start << std::endl;
			this->output.trigger((std::max(-WIDTH, std::min(WIDTH, static_cast<double>(left_start - right_start))) + WIDTH) / (2.*WIDTH));
			return;
		}
	}
}
