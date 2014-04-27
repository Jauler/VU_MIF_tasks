
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
	cout << WorkerDecorator::getName() + " is Managing something\n";
	WorkerDecorator::work();

	return;
}

void ManagerDecorator::raiseWage(int amount, Worker *happyW)
{
	cout << happyW->getName() + " Wage is being rased by " << amount << endl;

	happyW->setWage(happyW->getWage() + amount);

	return;
}
