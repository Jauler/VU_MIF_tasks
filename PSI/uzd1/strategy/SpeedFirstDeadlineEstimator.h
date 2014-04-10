

#ifndef __SPEED_DEADLINE_ESTIMATOR
#define __SPEED_DEADLINE_ESTIMATOR

#include "TimeEstimator.h"

class SpeedFirstDeadlineEstimator {
private:
	TimeEstimator te;

public:
	//Our contructor, requires TimeEstimator
	SpeedFirstDeadlineEstimator(TimeEstimator _te);

	//calculate how much time to deadline
	int calcTimeToDeadline(int difficulty);

};



#endif
