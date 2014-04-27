

#ifndef __CODER_EXTENSION_H
#define __CODER_EXTENSION_H

#include "WorkerDecorator.h"

class CoderDecorator : public WorkerDecorator {

public:
	CoderDecorator(Worker *_w);
	void work();



};

#endif
