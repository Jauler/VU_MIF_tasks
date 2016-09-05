

#ifndef TM_QUALITY_FIRST_TEAM_C_DEADLINE_ESTIMATOR
#define TM_QUALITY_FIRST_TEAM_C_DEADLINE_ESTIMATOR

#include "TM_QualityFirstDeadlineEstimator.h"

class TM_QualityFirstTeamCDeadlineEstimator : public TM_QualityFirstDeadlineEstimator {
public:

	int calcWorkingTime(int difficulty);
	int calcWorkingSpeed(int difficulty);
	int calcRequiredWorkingDays(int difficulty);
};


#endif
