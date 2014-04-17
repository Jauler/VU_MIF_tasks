
#include "TM_SpeedFirstDeadlineEstimator.h"


int TM_SpeedFirstDeadlineEstimator::calcTimeToDeadline(int difficulty)
{
	//If we value speed, then we would like to publish deadline:
		//*with added time for difficulty (more difficult to implement - more debug)
		//*with added a little time due high working capacity
		//	This team gets tired and works worse on longer projects
		//*with decreased time for speed, because we care about fastness here

	int tToDeadline;
	tToDeadline = calcRequiredWorkingDays(difficulty);
	tToDeadline += difficulty / 3;
	tToDeadline += calcWorkingTime(difficulty) / 14;
	tToDeadline -= calcWorkingSpeed(difficulty) / 10;

	return tToDeadline;
}

