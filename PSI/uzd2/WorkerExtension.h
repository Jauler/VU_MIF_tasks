

#ifndef __WORKER_EXTENSION_H
#define __WORKER_EXTENSION_H

#include "Worker.h"

class WorkerExtension : public Worker {
protected:
	Worker w;

public:
	WorkerExtension(Worker _w);
	virtual void work(){};

};





#endif
