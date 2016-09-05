/*
	Socket controlling stuff of the IRC client

	Author: Rytis Karpuška
		rytis@elektromotus.lt

*/

#ifndef __COMMUNICATOR_H
#define __COMMUNICATOR_H

#include <iostream>
#include <thread>

class Communicator {
public:
	Communicator(char *ipAddr, int port);
	bool connectToServer();

	int connFD;//needed for reader
	bool connected; //neede for reader

	virtual void onRead(char *buff, int size){};
	bool writeToServer(char *buff, int size);

private:
	char ipAddr[16]; //maximum size of string is 16
	int port;
	std::thread *readingThread;
};


#endif
