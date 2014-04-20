

#ifndef __TM_SPEED_FIRST_DEADLINE_ESTIMATOR
#define __TM_SPEED_FIRST_DEADLINE_ESTIMATOR

#include "../app/DeadlineEstimator.h"

class TM_SpeedFirstDeadlineEstimator : public DeadlineEstimator {
protected:
	virtual int calcWorkingTime(int difficulty){};
	virtual int calcWorkingSpeed(int difficulty){};
	virtual int calcRequiredWorkingDays(int difficulty){};

public:

	int calcTimeToDeadline(int difficulty);

};






#endif
