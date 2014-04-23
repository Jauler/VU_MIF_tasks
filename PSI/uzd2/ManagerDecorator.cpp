
#include <iostream>
#include "ManagerDecorator.h"

using namespace std;


ManagerDecorator::ManagerDecorator(Worker *_w) :
		WorkerDecorator(_w)
{
	return;
}

void ManagerDecorator::work()
{
	cout << w->getName() + " is Managing something\n";
	WorkerDecorator::work();

	return;
}

void ManagerDecorator::raiseWage(int amount, Worker *w)
{
	cout << w->getName() + " Wage is being rased by " << amount << endl;

	w->setWage(w->getWage() + amount);

	return;
}
