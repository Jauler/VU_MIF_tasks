

#ifndef __TEAM_B_TIME_EST_H
#define __TEAM_B_TIME_EST_H

#include "TimeEstimator.h"

class TeamBTimeEstimator : public TimeEstimator {
public:
	int calcWorkingTime(int difficulty);
	int calcWorkingSpeed(int difficulty);
	int calcRequiredWorkingDays(int difficulty);

};



#endif
