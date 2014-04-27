

#ifndef __MANAGER_EXTENSION_H
#define __MANAGER_EXTENSION_H

#include "Worker.h"
#include "WorkerExtension.h"

class ManagerExtension : public WorkerExtension {
private:
	Worker *w;
public:
	ManagerExtension(Worker *_w);
	void work();
	void raiseWage(int amount, Worker *w);



};

#endif
