
#include <iostream>
#include "ManagerExtension.h"

using namespace std;


ManagerExtension::ManagerExtension(Worker *_w):w(_w)
{
	return;
}

void ManagerExtension::work()
{
	cout << w->getName() + " is Managing something\n";

	if(next != NULL)
		next->work();

	return;
}

void ManagerExtension::raiseWage(int amount, Worker *happyW)
{
	cout << happyW->getName() + " Wage is being rased by " << amount << endl;

	happyW->setWage(happyW->getWage() + amount);

	return;
}
