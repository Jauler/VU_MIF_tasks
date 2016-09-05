

#ifndef __TESTER_EXTENSION_H
#define __TESTER_EXTENSION_H

#include "Worker.h"
#include "WorkerExtension.h"

class TesterExtension : public WorkerExtension {
private:
	Worker *w;
public:
	TesterExtension(Worker *_w);
	void work();



};

#endif

