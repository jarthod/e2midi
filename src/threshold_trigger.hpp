#ifndef THRESHOLD_TRIGGER_HPP
#define THRESHOLD_TRIGGER_HPP

#include <deque>
#include "trigger.hpp"

class ThresholdTrigger: public Trigger
{
	public:
    enum trigerState {
      UNTRIGGERED,
      TRIGGERING,
      TRIGGERED
    };
    static const stk::StkFloat  THRESHOLD;
    static const double         WIDTH;
    static const int            AVG_WIDTH;
		ThresholdTrigger(Output& output);
		void  feedMe(stk::StkFloat* samples, unsigned int buffSize);
    int   evaluateTimeDifference();

	private:
    void        displaySample(stk::StkFloat left, stk::StkFloat right);
		Output& output;
    std::deque<stk::StkFloat>  last_vals;
};

#endif /* THRESHOLD_TRIGGER_HPP */
