
#include <iostream>
#include "CoderExtension.h"

using namespace std;


CoderExtension::CoderExtension(Worker _w) :
		WorkerExtension(_w)
{
	return;
}

void CoderExtension::work()
{
	cout << w.getName() + " is Coding something\n";

	return;
}
