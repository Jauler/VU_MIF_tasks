
#include <iostream>
#include "DesignerExtension.h"

using namespace std;

DesignerExtension::DesignerExtension(Worker *_w):w(_w)
{
	return;
}

void DesignerExtension::work()
{
	cout << w->getName() + " is Designing something\n";

	if(next != NULL)
		next->work();

	return;
}
