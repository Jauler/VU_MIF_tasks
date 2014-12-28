

#ifndef __DESIGNER_EXTENSION_H
#define __DESIGNER_EXTENSION_H

#include "WorkerDecorator.h"

class DesignerDecorator : public WorkerDecorator {

public:
	DesignerDecorator(Worker *_w);
	void work();



};

#endif
