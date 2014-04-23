

#ifndef __MANAGER_EXTENSION_H
#define __MANAGER_EXTENSION_H

#include "WorkerDecorator.h"

class ManagerDecorator : public WorkerDecorator {

public:
	ManagerDecorator(Worker *_w);
	void work();
	void raiseWage(int amount, Worker *w);



};

#endif
