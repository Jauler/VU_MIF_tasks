

#include <typeinfo>
#include "WorkerExtension.h"



WorkerExtension::WorkerExtension(Worker *_w) :
		w(_w),
		Worker(_w->getName(), _w->getWage())
{
	return;
}

WorkerExtension *WorkerExtension::getRole(Worker *w, string role)
{
	//TODO:implement

}
