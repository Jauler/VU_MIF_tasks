
#include <iostream>
#include "TesterDecorator.h"

using namespace std;


TesterDecorator::TesterDecorator(Worker *_w) :
		WorkerDecorator(_w)
{
	return;
}

void TesterDecorator::work()
{
	cout << w->getName() + " is Testing something\n";
	WorkerDecorator::work();

	return;
}
