

#include <typeinfo>
#include "WorkerDecorator.h"



WorkerDecorator::WorkerDecorator(Worker *_w) :
		w(_w),
		Worker(_w->getName(), _w->getWage())
{
	return;
}

WorkerDecorator *WorkerDecorator::getRole(Worker *w, string role)
{
	//TODO:implement

}
