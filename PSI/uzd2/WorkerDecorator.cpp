

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

WorkerDecorator *WorkerDecorator::removeRole(string role)
{
	//We cannot remove actual worker
	if(role == "Worker")
		return NULL;

	//see if we our parent is Worker or WorkerDecorator
	WorkerDecorator *tmpW = dynamic_cast<WorkerDecorator *>(w);

	//If this is our role - we should return its worker
	string className(typeid(*this).name());
	if(className.find(role) != string::npos){
		if(tmpW != NULL) ((WorkerDecorator *)w)->removeRole(role);
		return (WorkerDecorator *)w;
	}

	//If this is the first decorator before Worker, we cannot remove anything
	//check for that
	if(tmpW == NULL)
		return NULL;

	//Check if this is the one needed changin
	string workerClassName(typeid(*w).name());
	if(workerClassName.find(role) != string::npos){
		w = ((WorkerDecorator *)w)->removeRole(role);
		removeRole(role); //Do not stop here, because there might be more roles
		return this;
	}

	//Go deeper into recursive world
	if(tmpW->removeRole(role))
		return this;
	else
		return NULL;
}




