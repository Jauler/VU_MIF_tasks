
#include <iostream>
#include "ManagerExtension.h"

using namespace std;


ManagerExtension::ManagerExtension(Worker *_w) :
		WorkerExtension(_w)
{
	return;
}

void ManagerExtension::work()
{
	cout << w->getName() + " is Managing something\n";
	WorkerExtension::work();

	return;
}

void ManagerExtension::raiseWage(int amount, Worker *w)
{
	cout << w->getName() + " Wage is being rased by " << amount << endl;

	w->setWage(w->getWage() + amount);

	return;
}
