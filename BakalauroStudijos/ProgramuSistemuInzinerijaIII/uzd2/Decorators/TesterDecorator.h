

#ifndef __TESTER_EXTENSION_H
#define __TESTER_EXTENSION_H

#include "WorkerDecorator.h"

class TesterDecorator : public WorkerDecorator {

public:
	TesterDecorator(Worker *_w);
	void work();



};

#endif
