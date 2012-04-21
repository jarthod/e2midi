#ifndef THRESHOLD_TRIGGER_HPP
#define THRESHOLD_TRIGGER_HPP

#include <deque>
#include "trigger.hpp"

class ThresholdTrigger: public Trigger
{
	public:
    static const stk::StkFloat THRESHOLD;
    static const double         WIDTH;
		ThresholdTrigger(Output& output);
		virtual void feedMe(stk::StkFloat* samples, unsigned int buffSize);

	private:
		Output& output;
};

#endif /* THRESHOLD_TRIGGER_HPP */
