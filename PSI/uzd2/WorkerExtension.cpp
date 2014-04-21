

#include "WorkerExtension.h"



WorkerExtension::WorkerExtension(Worker *_w) :
		w(_w),
		Worker(_w->getName(), _w->getWage())
{
	return;
}
