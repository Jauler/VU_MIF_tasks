

#include "WorkerExtension.h"




WorkerExtension::WorkerExtension(Worker _w) : Worker(_w.getName(), _w.getWage())
{
	w = _w;
	return;
}
