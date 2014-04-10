

#ifndef __QUALITY_DEADLINE_ESTIMATOR
#define __QUALITY_DEADLINE_ESTIMATOR

#include "TimeEstimator.h"

class QualityFirstDeadlineEstimator {
private:
	TimeEstimator te;
public:
	QualityFirstDeadlineEstimator(TimeEstimator _te);

	int calcTimeToDeadline(int difficulty);

};



#endif
