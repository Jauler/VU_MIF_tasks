

#ifndef TM_SPEED_FIRST_TEAM_A_DEADLINE_ESTIMATOR
#define TM_SPEED_FIRST_TEAM_A_DEADLINE_ESTIMATOR

#include "TM_TeamATimeEstimator.h"
#include "TM_SpeedFirstDeadlineEstimator.h"

class TM_SpeedFirstTeamADeadlineEstimator : public TM_SpeedFirstDeadlineEstimator {
private:
	TM_TeamATimeEstimator te;

public:

	int calcWorkingTime(int difficulty);
	int calcWorkingSpeed(int difficulty);
	int calcRequiredWorkingDays(int difficulty);
};


#endif
