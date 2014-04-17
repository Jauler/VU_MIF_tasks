
#include "TM_SpeedFirstTeamBDeadlineEstimator.h"

int TM_SpeedFirstTeamBDeadlineEstimator::calcWorkingTime(int difficulty)
{
	//Lets say, that this is the formula to calculate actual working time from difficulty
	return te.calcWorkingTime(difficulty);
}


int TM_SpeedFirstTeamBDeadlineEstimator::calcWorkingSpeed(int difficulty)
{
	//Lets say, that this team working speed depends a lot difficulty
	return te.calcWorkingSpeed(difficulty);
}


int TM_SpeedFirstTeamBDeadlineEstimator::calcRequiredWorkingDays(int difficulty)
{
	//this team only works every second day, and 8 hours a day

	//NOTE: multiplying by one is to illustrate that this team is working every day
	//	compiler will optimize this out anyway
	return te.calcRequiredWorkingDays(difficulty);
}
