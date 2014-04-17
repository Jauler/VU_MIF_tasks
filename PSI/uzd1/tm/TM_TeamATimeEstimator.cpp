
#include "TM_TeamATimeEstimator.h"

int TM_TeamATimeEstimator::calcWorkingTime(int difficulty)
{
	//Lets say, that this is the formula to calculate actual working time from difficulty
	return 5 + difficulty / 4 + 3;
}


int TM_TeamATimeEstimator::calcWorkingSpeed(int difficulty)
{
	//Lets say, that this team working speed depends only a little on difficulty
	return 15 + difficulty / 4;
}


int TM_TeamATimeEstimator::calcRequiredWorkingDays(int difficulty)
{
	//this team only works every second day, and 8 hours a day
	return calcWorkingTime(difficulty) * 2 / 8;
}


