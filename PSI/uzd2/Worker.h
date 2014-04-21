

#ifndef __WORKER_H
#define __WORKER_H

#include <string>
#include <iostream>

using namespace std;

class Worker {
private:
	string name;
	int wage;

public:
	Worker(string _name, int wage){name = _name;};
	string getName(){return name;};
	int getWage(){return wage;};
	void setWage(int _wage){wage = _wage;};
	virtual void work(){cout << name + " is Working\n";};


};


#endif
