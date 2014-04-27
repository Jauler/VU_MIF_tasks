

#ifndef __DESIGNER_EXTENSION_H
#define __DESIGNER_EXTENSION_H

#include "Worker.h"
#include "WorkerExtension.h"

class DesignerExtension : public WorkerExtension {
private:
	Worker *w;
public:
	DesignerExtension(Worker *_w);
	void work();



};

#endif

