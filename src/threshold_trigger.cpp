#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <math.h>
#include "threshold_trigger.hpp"

const stk::StkFloat ThresholdTrigger::WIDTH = 10;
const double ThresholdTrigger::THRESHOLD = 2;
const int ThresholdTrigger::AVG_WIDTH = 40;
	
ThresholdTrigger::ThresholdTrigger(Output& output)
: Trigger(output), output(output)
{}

void ThresholdTrigger::displaySample(stk::StkFloat left, stk::StkFloat right)
{
	const int cols = 80;
	int lval = round(left * cols/2.0);
	if (lval >= 0) {
		for(int i = 0; i < cols/2; i++)
			std::cout << ' ';
		std::cout << '|';
		for(int i = 0; i < lval; i++)
			std::cout << '#';
		for(int i = lval; i < cols/2; i++)
			std::cout << ' ';
	} else {
		for(int i = -lval; i < cols/2; i++)
			std::cout << ' ';	
		for(int i = 0; i < -lval; i++)
			std::cout << '#';
		std::cout << '|';
		for(int i = 0; i < cols/2; i++)
			std::cout << ' ';
	}
	int rval = round(right * cols/2.0);
	if (rval >= 0) {
		for(int i = 0; i < cols/2; i++)
			std::cout << ' ';
		std::cout << '|';
		for(int i = 0; i < rval; i++)
			std::cout << '#';
		for(int i = rval; i < cols/2; i++)
			std::cout << ' ';
	} else {
		for(int i = -rval; i < cols/2; i++)
			std::cout << ' ';	
		for(int i = 0; i < -rval; i++)
			std::cout << '#';
		std::cout << '|';
		for(int i = 0; i < cols/2; i++)
			std::cout << ' ';
	}
	std::cout << left << " - " << right << std::endl;
}
		
int	ThresholdTrigger::evaluateTimeDifference()
{
	int	res = -WIDTH;
	double bestScore = 999;
	for (int shift = -WIDTH; shift <= WIDTH; shift++) {
		double score = 0;
		for (int l = 0; l < AVG_WIDTH; l++) {
			int r = l + shift;
			if (r >= 0 && r < AVG_WIDTH) {
				score += pow(last_vals[l*2] - last_vals[r*2+1], 2);
			}
		}
		if (score < bestScore) {
			bestScore = score;
			res = shift;
		}
	}
	int cross = 0;
	for (int l = 2; l < AVG_WIDTH*2; l+=2) {
		if (last_vals[l] * last_vals[l-2] < 0)
			cross++;
		if (last_vals[l+1] * last_vals[l-1] < 0)
			cross++;
	}
	if (cross < 10)
		res = -9999;
	return res;
}

void ThresholdTrigger::feedMe(stk::StkFloat *samples, unsigned int buffSize)
{
	static stk::StkFloat lavg = 0, ravg = 0;
	int left_start = -1;
	int right_start = -1;
	static trigerState state = UNTRIGGERED;
	std::stringstream	out;

	for (unsigned int i = 0; i < buffSize * 2; i += 2)
	{
		// Add abs to avg window
		lavg += fabs(samples[i]);
		ravg += fabs(samples[i + 1]);
		// Add values to queue
		last_vals.push_back(samples[i]);
		last_vals.push_back(samples[i + 1]);
		if (last_vals.size() >= AVG_WIDTH * 2) {
			lavg -= fabs(last_vals.front());
			last_vals.pop_front();
			ravg -= fabs(last_vals.front());
			last_vals.pop_front();
		}
		if (state == UNTRIGGERED && ((i/2) - left_start) > (WIDTH * 2))
			left_start = -1;
		if (state == UNTRIGGERED && ((i/2) - right_start) > (WIDTH * 2))
			right_start = -1;
		if ((left_start < 0) && (lavg > THRESHOLD))
			left_start = i / 2;
		if ((right_start < 0) && (ravg > THRESHOLD))
			right_start = i / 2;
		if (state == TRIGGERED && (lavg < THRESHOLD / 1.2 || ravg < THRESHOLD / 1.2)) {
			state = UNTRIGGERED;
			right_start = -1;
			left_start = -1;
		}
		if (state == TRIGGERING) {
		//	displaySample(samples[i], samples[i+1]);
		}
		if (state == TRIGGERING && (i/2) == (std::max(left_start, right_start) + (AVG_WIDTH / 2))) {
			int diff = evaluateTimeDifference();
			//std::cout << "trigger ! " << lavg << " - " << ravg << " - " << left_start << " - " << right_start << " (" << diff << ")" << std::endl;
			if (diff == -9999) {
				//std::cout << "false positive !!!" << std::endl;
			} else {
				this->output.trigger((std::max(-WIDTH, std::min(WIDTH, static_cast<double>(diff))) + WIDTH) / (2.*WIDTH));				
			}
			state = TRIGGERED;
		}

		// Tap detection
		if (state == UNTRIGGERED && left_start >= 0 && right_start >= 0) {
			//std::cerr << out.rdbuf();
			//out.clear();
			//for (unsigned j = 0; j < last_vals.size(); j+= 2) {
			//	displaySample(last_vals[j], last_vals[j+1]);
			//}
			//std::cout << "detection ! " << lavg << " - " << ravg << " - " << left_start << " - " << right_start << " (" << (left_start - right_start) << ")" << std::endl;
			state = TRIGGERING;
		}
	}
}
