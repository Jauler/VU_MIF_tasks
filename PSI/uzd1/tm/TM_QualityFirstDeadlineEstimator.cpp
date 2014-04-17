
#include "TM_QualityFirstDeadlineEstimator.h"


int TM_QualityFirstDeadlineEstimator::calcTimeToDeadline(int difficulty)
{
	//TODO: update coments
	//If we value quality, then we would like to publish deadline:
		//*with added time for difficulty (more difficult to implement - more debug)
		//*with removed a little time due high working capacity (better focused)
		//*with added some time for speed, because doing things fast, introduces errors

	int tToDeadline;
	tToDeadline = calcRequiredWorkingDays(difficulty);
	tToDeadline += difficulty * 4;
	tToDeadline += calcWorkingTime(difficulty) / 5;
	tToDeadline -= calcWorkingSpeed(difficulty) / 12;

	return tToDeadline;
}
