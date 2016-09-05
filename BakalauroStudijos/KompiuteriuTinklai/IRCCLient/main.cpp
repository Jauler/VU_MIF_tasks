#include <iostream>

#include <stdlib.h>
#include <stdio.h>

#include "IRCParser.h"

using namespace std;

class Printer : public IRCParser {
public:
	Printer(char *ipAddr, int port) : IRCParser(ipAddr, port){};

	bool onMsgReceived(string from, string msg){
		printf("%s:%s\n", from.c_str(), msg.c_str());
		return true;
	}
};



int main(int argc, char *argv[])
{
	printf("Welcome to a little IRC client program\n");

	if(argc != 5){
		printf("Please specify IP address and port as CLI arguments\n");
		return 0;
	}

	int port = 0;
	try {
		string strPort(argv[2]);
		port = std::stoi(strPort);
	} catch(...){
		printf("Port number must be number between 1024 and 65536\n");
	}

	Printer parser(argv[1], port);

	parser.msgNICK(string(argv[3]));
	parser.msgUSER(string(argv[3]), 0, "Rytis Karpuška");
	usleep(100000);
	parser.msgJOIN(string(argv[4]));
	sleep(1);

	if(parser.getChannel() != string(argv[4])){
		printf("Could not connect to channel \"%s\"%s\"\n",
				parser.getChannel().c_str(), argv[4]);
		return 0;
	}


	int i = 0;
	while(parser.connected){
		string msg;
		cin >> msg;
		parser.msgPRIVMSG(string(argv[4]), msg);
	}

	printf("we have been disconnected\n");

	return 0;
}
