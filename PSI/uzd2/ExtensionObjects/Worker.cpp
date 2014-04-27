
#include <stdio.h>
#include <typeinfo>
#include <cxxabi.h>
#include "Worker.h"

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

Worker::Worker(string _name, int _wage):
		extensions(NULL),
		name(_name),
		wage(_wage)
{
	return;
}

string Worker::getName()
{
	return name;
}

int Worker::getWage()
{
	return wage;
}

void Worker::setWage(int _wage)
{
	wage = _wage;

	cout << name + " wage is set to " << _wage << endl;

	return;
}

void Worker::work()
{
	if(extensions != NULL)
		extensions->work();

	cout << name + " is working\n";
	return;
}


//************** Extension managemenet**********************
void Worker::addExtension(WorkerExtension *we)
{
	//If nothing has been added, just add and dont care about nexts
	if(extensions == NULL){
		extensions = we;
		return;
	}

	//Find last in a chain
	WorkerExtension *extLast = extensions;
	while(extLast->next != NULL)
		extLast = extLast->next;

	//take care of next links
	extLast->next = we;

	return;
}

WorkerExtension *Worker::getExtension(string extension)
{
	WorkerExtension *we = extensions;

	while(we != NULL){
		//get clean class name
		string className = DemangleName(typeid(*we).name());
		if(className == extension)
			return we;

		//Go futher
		we = we->next;
	}

	return NULL;
}

int Worker::rmExtension(string extension)
{
	int status = FAILURE;

	//check if at least one extension is here
	if(extensions == NULL)
		return FAILURE;

	//check if the first one is what we want to remove
	string className = DemangleName(typeid(*extensions).name());
	if(className == extension){
		extensions = extensions->next;
		if(extensions == NULL) return SUCCESS;
	}

	//Search for the extension
	WorkerExtension *currExt = extensions;
	while(currExt->next != NULL){
		//check if we need to remove this
		className = DemangleName(typeid(*currExt->next).name());
		if(className == extension){
			currExt->next = currExt->next->next;
			status = SUCCESS;
			continue;
		}

		//Go further
		currExt = currExt->next;
	}

	//If all of classes were our classes, we have to delete last one
	className = DemangleName(typeid(*extensions).name());
	if(className == extension){
		extensions = NULL;
	}

	return status;
}



//**********************************************************
