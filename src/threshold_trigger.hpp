#ifndef THRESHOLD_TRIGGER_HPP
#define THRESHOLD_TRIGGER_HPP

#include "trigger.hpp"

class ThresholfTrigger: Trigger
{
	public:
		ThresholfTrigger(Output& output);
		feedMe(StkFloat* samples, unsigned int buffSize);

	private:
		THRESHOLD = 0.001
		Output& output;
};

#encdif /* THRESHOLD_TRIGGER_HPP */
