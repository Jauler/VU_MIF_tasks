

#ifndef __DESIGNER_EXTENSION_H
#define __DESIGNER_EXTENSION_H

#include "WorkerExtension.h"

class DesignerExtension : public WorkerExtension {

public:
	DesignerExtension(Worker *_w);
	void work();



};

#endif
