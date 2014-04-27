
#include <iostream>
#include "CoderDecorator.h"

using namespace std;


CoderDecorator::CoderDecorator(Worker *_w) :
		WorkerDecorator(_w)
{
	return;
}

void CoderDecorator::work()
{
	cout << WorkerDecorator::getName() + " is Coding something\n";
	WorkerDecorator::work();

	return;
}
