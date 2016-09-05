

#ifndef __QUALITY_DEADLINE_ESTIMATOR
#define __QUALITY_DEADLINE_ESTIMATOR

#include "../app/DeadlineEstimator.h"
#include "TimeEstimator.h"

class QualityFirstDeadlineEstimator : public DeadlineEstimator {
private:
	TimeEstimator *te;

public:
	QualityFirstDeadlineEstimator(TimeEstimator *_te);

	int calcTimeToDeadline(int difficulty);

};



#endif
