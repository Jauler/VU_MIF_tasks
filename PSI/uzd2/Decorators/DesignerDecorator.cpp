
#include <iostream>
#include "DesignerDecorator.h"

using namespace std;


DesignerDecorator::DesignerDecorator(Worker *_w) :
		WorkerDecorator(_w)
{
	return;
}

void DesignerDecorator::work()
{
	cout << WorkerDecorator::getName() + " is Designing something\n";
	WorkerDecorator::work();

	return;
}
