

#ifndef __TEAM_A_TIME_EST_H
#define __TEAM_A_TIME_EST_H

#include "TimeEstimator.h"

class TeamATimeEstimator : public TimeEstimator {
public:
	int calcWorkingTime(int difficulty);
	int calcWorkingSpeed(int difficulty);
	int calcRequiredWorkingDays(int difficulty);

};



#endif
