

#ifndef __TESTER_EXTENSION_H
#define __TESTER_EXTENSION_H

#include "WorkerExtension.h"

class TesterExtension : public WorkerExtension {

public:
	TesterExtension(Worker _w);
	void work();



};

#endif
