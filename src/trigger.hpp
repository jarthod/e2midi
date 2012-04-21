#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include <output.hpp>

class Trigger
{
	public:
		Trigger(Output&) {};
		void feedMe(StkFloat *samples, unsigned int buffSize) = 0;
};

#endif /* TRIGGER_HPP */
