#ifndef THRESHOLD_TRIGGER_HPP
#define THRESHOLD_TRIGGER_HPP

#include "trigger.hpp"

class ThresholfTrigger: Trigger
{
	public:
		ThresholfTrigger(Output& output);
		virtual void feedMe(stk::StkFloat* samples, unsigned int buffSize);

	private:
		static const stk::StkFloat THRESHOLD = 0.001;
		Output& output;
};

#endif /* THRESHOLD_TRIGGER_HPP */
