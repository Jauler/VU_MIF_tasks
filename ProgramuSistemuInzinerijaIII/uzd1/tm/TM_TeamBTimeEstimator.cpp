
#include "TM_TeamBTimeEstimator.h"

int TM_TeamBTimeEstimator::calcWorkingTime(int difficulty)
{
	//Lets say, that this is the formula to calculate actual working time from difficulty
	return difficulty * 15 + 3;
}


int TM_TeamBTimeEstimator::calcWorkingSpeed(int difficulty)
{
	//Lets say, that this team working speed depends hardly on difficulty
	return 3 + difficulty * 4;
}


int TM_TeamBTimeEstimator::calcRequiredWorkingDays(int difficulty)
{
	//this team works every day

	//NOTE: multiplying by one is to illustrate that this team is working every day
	//	compiler will optimize this out anyway
	return calcWorkingTime(difficulty) * 1;
}


