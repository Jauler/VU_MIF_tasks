
#include <iostream>
#include "DesignerExtension.h"

using namespace std;


DesignerExtension::DesignerExtension(Worker _w) :
		WorkerExtension(_w)
{
	return;
}

void DesignerExtension::work()
{
	cout << w.getName() + " is Designing something\n";

	return;
}
