/*
	Message parser for IRC client

	Author: Rytis Karpuška
		rytis@elektromotus.lt

*/

#ifndef __IRC_PARSER_H
#define __IRC_PARSER_H

#include "communicator.h"

using namespace std;

class IRCParser : public Communicator {
public:
	IRCParser(char *ipAddr, int port);

	void onRead(char *buff, int size);
	string getChannel();

	//send commands
	bool msgPASS(string pass);

	bool msgNICK(string nick);

	bool msgUSER(string user, int mode, string realname);

	bool msgJOIN(string channel);
	bool msgJOIN(string channel, string key);
	bool rspJOIN(string cmd);

	bool msgPRIVMSG(string target, string message);
	bool rspPRIVMSG(string cmd);

	virtual bool onMsgReceived(string from, string msg){};

protected:
	string cmdEnd;
	string joinedChannel;

};



#endif
