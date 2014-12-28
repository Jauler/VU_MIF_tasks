/*

	Program entry point for 3D mouse demonstration
	Author: Rytis Karpuška
		rytis@elektromotus.lt

*/

#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

#include "connector.h"
#include "drawer.h"

static pthread_t server_thread;

int main(int argc, char *argv[])
{
	pthread_create(&server_thread, NULL, (void *(*)(void *))connector_run, NULL);

	drawer_run(argc, argv);

	//TODO: pthread_join
	exit(0);
	return 0;
}
