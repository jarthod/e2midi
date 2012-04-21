#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include "RtAudio.h"
#include "SineWave.h"
#include "output.hpp"

class Trigger
{
	public:
		Trigger(Output&) {};
		virtual void feedMe(stk::StkFloat *samples, unsigned int buffSize) = 0;
};

#endif /* TRIGGER_HPP */
