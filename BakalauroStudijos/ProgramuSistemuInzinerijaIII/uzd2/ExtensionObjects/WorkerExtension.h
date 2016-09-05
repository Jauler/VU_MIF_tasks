

#ifndef __WORKER_EXTENSIONS_H
#define __WORKER_EXTENSIONS_H

#include <string>

using namespace std;

class WorkerExtension {
public:
	WorkerExtension():next(NULL){}

	WorkerExtension *next;
	virtual void work(){cout << "Worker is working\n";};

};



#endif
