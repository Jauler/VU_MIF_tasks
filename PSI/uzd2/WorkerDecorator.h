

#ifndef __WORKER_EXTENSION_H
#define __WORKER_EXTENSION_H

#include <string>
#include "Worker.h"

using namespace std;

const int SUCCESS = 1;
const int FAILURE = 0;



class WorkerDecorator : public Worker {
protected:
	Worker *w;

public:
	WorkerDecorator(Worker *_w);
	virtual void work(){w->work();};

	//Decorator interface
	WorkerDecorator *getRole(string role);
	WorkerDecorator *removeRole(string role);

};

#endif
