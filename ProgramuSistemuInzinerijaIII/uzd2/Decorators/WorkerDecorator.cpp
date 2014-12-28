

#include <string>
#include <typeinfo>
#include "WorkerDecorator.h"
#include <cxxabi.h>

using namespace std;

static string DemangleName(const char *name)
{
	int status;
	char *realName = abi::__cxa_demangle(name, 0, 0, &status);
	if(status != 0)
		return "";

	string realNameStr = string(realName);
	delete realName;
	return realNameStr;
}

WorkerDecorator::WorkerDecorator(Worker *_w) :
		w(_w),
		Worker(_w->getName(), _w->getWage())
{
	return;
}

WorkerDecorator *WorkerDecorator::getRole(string role)
{
	//If we are the role we are looking for
	string className = DemangleName(typeid(*this).name());
	if(className == role)
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
	string className = DemangleName(typeid(*this).name());
	if(className == role){
		if(tmpW != NULL) ((WorkerDecorator *)w)->removeRole(role);
		return (WorkerDecorator *)w;
	}

	//If this is the first decorator before Worker, we cannot remove anything
	//check for that
	if(tmpW == NULL)
		return NULL;

	//Check if this is the one needed changin
	string workerClassName = DemangleName(typeid(*w).name());
	if(workerClassName == role){
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




