

#ifndef __CODER_EXTENSION_H
#define __CODER_EXTENSION_H

#include "WorkerExtension.h"

class CoderExtension : public WorkerExtension {

public:
	CoderExtension(Worker _w);
	void work();



};

#endif
