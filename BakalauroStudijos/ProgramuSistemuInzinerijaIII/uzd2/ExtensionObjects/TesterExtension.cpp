
#include <iostream>
#include "TesterExtension.h"

using namespace std;

TesterExtension::TesterExtension(Worker *_w):w(_w)
{
	return;
}

void TesterExtension::work()
{
	cout << w->getName() + " is Testing something\n";

	if(next != NULL)
		next->work();

	return;
}
