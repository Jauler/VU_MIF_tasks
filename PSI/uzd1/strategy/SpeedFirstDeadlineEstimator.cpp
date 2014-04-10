
#include "SpeedFirstDeadlineEstimator.h"


SpeedFirstDeadlineEstimator::SpeedFirstDeadlineEstimator(TimeEstimator _te)
{
	//save our time estimator
	te = _te;
	return;
}


int SpeedFirstDeadlineEstimator::calcTimeToDeadline(int difficulty)
{
	//If we value quality, then we would like to publish deadline:
		//*with added time for difficulty (more difficult to implement - more debug)
		//*with added a little time due high working capacity
		//	This team gets tired and works worse on longer projects
		//*with decreased time for speed, because we care about fastness here

	int tToDeadline;
	tToDeadline = te.calcRequiredWorkingDays(difficulty);
	tToDeadline += difficulty / 2;
	tToDeadline += te.calcWorkingTime(difficulty);
	tToDeadline -= te.calcWorkingSpeed(difficulty) / 10;

	return tToDeadline;
}
