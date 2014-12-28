

#ifndef __WORKER_H
#define __WORKER_H

#include <string>
#include <iostream>

using namespace std;

class Worker {
public:
	string name;
	int wage;

	Worker(string _name, int _wage){name = _name; wage = _wage;};
	virtual string getName(){return name;};
	virtual int getWage(){return wage;};
	virtual void setWage(int _wage){wage = _wage; cout << name << " wage set" << endl;};
	virtual void work(){cout << name << " is Working\n"; wage++;};


};


#endif
