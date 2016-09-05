


#ifndef __TIME_EST_H
#define __TIME_EST_H

class TimeEstimator {
public:
	virtual int calcWorkingTime(int difficulty){};
	virtual int calcWorkingSpeed(int difficulty){};
	virtual int calcRequiredWorkingDays(int difficulty){};
};



#endif
