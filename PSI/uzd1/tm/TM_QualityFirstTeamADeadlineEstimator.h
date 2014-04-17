

#ifndef TM_QUALITY_FIRST_TEAM_A_DEADLINE_ESTIMATOR
#define TM_QUALITY_FIRST_TEAM_A_DEADLINE_ESTIMATOR

#include "TM_QualityFirstDeadlineEstimator.h"

class TM_QualityFirstTeamADeadlineEstimator : public TM_QualityFirstDeadlineEstimator {
public:

	int calcWorkingTime(int difficulty);
	int calcWorkingSpeed(int difficulty);
	int calcRequiredWorkingDays(int difficulty);
};


#endif
