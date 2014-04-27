

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
	Worker(string _name, int _wage){name = _name; wage = _wage;};
	string getName(){return name;};
	int getWage(){return wage;};
	void setWage(int _wage){wage = _wage; cout << name << " Wage set to " << _wage;};
	virtual void work(){cout << name + " is Working\n";};


};


#endif
