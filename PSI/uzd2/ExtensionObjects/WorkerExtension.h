

#ifndef __WORKER_EXTENSIONS_H

#include <string>

using namespace std;

class WorkerExtension {
public:
	WorkerExtension():next(NULL){}
	WorkerExtension(WorkerExtension *we){};

	string extName;
	WorkerExtension *next;
	virtual void work();

};



#endif
