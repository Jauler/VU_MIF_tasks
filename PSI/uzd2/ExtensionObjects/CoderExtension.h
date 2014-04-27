

#ifndef __CODER_EXTENSION_H
#define __CODER_EXTENSION_H

#include "Worker.h"
#include "WorkerExtension.h"

class CoderExtension : public WorkerExtension {
private:
	Worker *w;
public:
	CoderExtension(Worker *_w);
	void work();
};

#endif

