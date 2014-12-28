
#include "TM_QualityFirstTeamADeadlineEstimator.h"

int TM_QualityFirstTeamADeadlineEstimator::calcWorkingTime(int difficulty)
{
	return te.calcWorkingTime(difficulty);
}


int TM_QualityFirstTeamADeadlineEstimator::calcWorkingSpeed(int difficulty)
{
	return te.calcWorkingSpeed(difficulty);
}


int TM_QualityFirstTeamADeadlineEstimator::calcRequiredWorkingDays(int difficulty)
{
	//this team only works every second day, and 8 hours a day
	return te.calcRequiredWorkingDays(difficulty);
}
