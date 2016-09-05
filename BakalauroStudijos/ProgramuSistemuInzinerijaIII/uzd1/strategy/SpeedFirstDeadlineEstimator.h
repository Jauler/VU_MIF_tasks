

#ifndef __SPEED_DEADLINE_ESTIMATOR
#define __SPEED_DEADLINE_ESTIMATOR

#include "../app/DeadlineEstimator.h"
#include "TimeEstimator.h"

class SpeedFirstDeadlineEstimator : public DeadlineEstimator {
private:
	TimeEstimator *te;

public:
	SpeedFirstDeadlineEstimator(TimeEstimator *_te);

	int calcTimeToDeadline(int difficulty);

};



#endif
