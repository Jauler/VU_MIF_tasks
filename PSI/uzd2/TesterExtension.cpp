
#include <iostream>
#include "TesterExtension.h"

using namespace std;


TesterExtension::TesterExtension(Worker *_w) :
		WorkerExtension(_w)
{
	return;
}

void TesterExtension::work()
{
	cout << w->getName() + " is Testing something\n";
	WorkerExtension::work();

	return;
}
