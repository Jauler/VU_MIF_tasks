
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

Worker::Worker(string _name, int _wage)
{
	extensions = NULL;
	name = _name;
	wage = _wage;

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

	return;
}

void Worker::work()
{
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

	//Add this extension to the first place
	extensions = we;

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

	return FAILURE;
}



//**********************************************************
