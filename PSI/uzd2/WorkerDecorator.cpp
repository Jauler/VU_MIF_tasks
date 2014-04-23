

#include <string>
#include <typeinfo>
#include "WorkerDecorator.h"

using namespace std;



WorkerDecorator::WorkerDecorator(Worker *_w) :
		w(_w),
		Worker(_w->getName(), _w->getWage())
{
	return;
}

WorkerDecorator *WorkerDecorator::getRole(string role)
{
	//if we are the role we are looking for
	string className(typeid(*this).name());

	if(className.find(role) != string::npos)
		return this;

	//try to go deeper
	WorkerDecorator *tmpW = dynamic_cast<WorkerDecorator *>(w);
	if(tmpW != NULL)
		return ((WorkerDecorator *)w)->getRole(role);

	//if there is nowhere to go
	return NULL;
}
