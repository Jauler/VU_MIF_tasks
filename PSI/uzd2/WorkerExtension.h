

#ifndef __WORKER_EXTENSION_H
#define __WORKER_EXTENSION_H

#include <string>
#include "Worker.h"

using namespace std;

class WorkerExtension : public Worker {
protected:
	Worker *w;

public:
	WorkerExtension(Worker *_w);
	virtual void work(){w->work();};

	//Extension interface
	WorkerExtension *getRole(Worker *w, string role);

};





#endif
