/*
	Socket controlling stuff of the IRC client

	Author: Rytis Karpuška
		rytis@elektromotus.lt

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "communicator.h"

static void reader(Communicator *comm)
{
	//read and if needed - onRead
	char buff[512]; //read buffer, according to RFC2812 - 512 is max
	int size;
	while((size = read(comm->connFD, buff, 512)) > 0){
		comm->onRead(buff, size);
		memset(buff, 0, sizeof(buff));
	}

	comm->connected = false;

	return;
}

Communicator::Communicator(char *_ipAddr, int _port)
{
	//copy address and port
	strncpy(ipAddr, _ipAddr, 15);
	ipAddr[15] = 0; //make sure string is null terminated
	port = _port;

	//initiate some default values
	connected = false;
	connFD = 0;
	readingThread = NULL;

	return;
}

bool Communicator::writeToServer(char *buff, int size)
{

	if(!connected)
		return false;

	//try to write data
	if(write(connFD, buff, size) != size)
		return false;

	return true;
}

bool Communicator::connectToServer()
{
	//create socket
	int sockFD = socket(AF_INET, SOCK_STREAM, 0);
	if(sockFD < 0){
		fprintf(stderr, "Could not open the socket\n");
	}

	//reset address structure
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	
	//convert server address to binary form
	if(inet_pton(AF_INET, ipAddr, &addr.sin_addr) < 0){
		printf("malformed server address\n");
		return false;
	}

	//connect socket to address
	if(connect(sockFD, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		printf("Could not connect to server\n");
		return false;
	}

	//save socket address
	connFD = sockFD;

	//start read thread
	readingThread = new std::thread(reader, this);

	connected = true;

	return true;
}
