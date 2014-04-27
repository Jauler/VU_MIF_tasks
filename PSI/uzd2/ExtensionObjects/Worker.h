

#ifndef __WORKER_H
#define __WORKER_H

#include <string>
#include <iostream>
#include "WorkerExtension.h"

using namespace std;

class Worker {
private:
	WorkerExtension *extensions;
	string name;
	int wage;

public:
	Worker(string _name, int _wage);
	string getName();
	int getWage();
	void setWage(int _wage);
	virtual void work();

	void addExtension(WorkerExtension *we);
	WorkerExtension *getExtension(string extension);
	int rmExtension(string extension);

	static const int SUCCESS = 1;
	static const int FAILURE = 0;
};


#endif
