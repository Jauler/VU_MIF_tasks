

#ifndef __MANAGER_EXTENSION_H
#define __MANAGER_EXTENSION_H

#include "WorkerExtension.h"

class ManagerExtension : public WorkerExtension {

public:
	ManagerExtension(Worker *_w);
	void work();
	void raiseWage(int amount, Worker *w);



};

#endif
