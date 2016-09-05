/*
	Message parser for IRC client

	Author: Rytis Karpuška
		rytis@elektromotus.lt

*/

#include <cstdlib>
#include <stdlib.h>

#include "IRCParser.h"

using namespace std;

IRCParser::IRCParser(char *ipAddr, int port) : Communicator(ipAddr, port)
{
	cmdEnd = "\n\r";

	connectToServer();

	return;
}


void IRCParser::onRead(char *buff, int size)
{
	string rxBuff(buff);
	int cmdEnd = rxBuff.find_first_of("\n\r");

	//create string data
	string rxCmd = rxBuff.substr(0, cmdEnd + 2);

	//find command string start and end places
	int cmdStart = 0, cmdPosEnd = 0;
	cmdStart = rxCmd.find_first_of(" ");
	cmdPosEnd   = rxCmd.find_first_of(" ", cmdStart + 1);

	if(cmdStart == 0 || cmdPosEnd - 1 <= cmdStart + 1)
		return;

	//extract command
	string cmd = rxCmd.substr(cmdStart + 1, cmdPosEnd - cmdStart - 1);

	if(cmd == "PRIVMSG")
		rspPRIVMSG(rxCmd);
	else if(cmd == "JOIN")
		rspJOIN(rxCmd);

	//check if we have some more commands at the same packet
	if(rxBuff.length() > cmdEnd + 2){
		int leftoverLen = rxBuff.length() - cmdEnd - 2;
		string leftoverData = rxBuff.substr(cmdEnd + 2, leftoverLen);
		onRead((char *)leftoverData.c_str(), leftoverLen);
	}

	return;
}


bool IRCParser::msgPASS(string pass)
{
	if(pass.length() > 500)
		return false;

	string cmd = "PASS ";
	cmd += pass;
	cmd += cmdEnd;
	

	writeToServer((char *)cmd.c_str(), cmd.length());

	return true;
}

bool IRCParser::msgNICK(string nick)
{
	if(nick.length() > 500)
		return false;

	string cmd = "NICK ";
	cmd += nick;
	cmd += cmdEnd;

	writeToServer((char *)cmd.c_str(), cmd.length());

	return true;
}

bool IRCParser::msgUSER(string user, int mode, string realname)
{
	//convert int to string
	string convertedMode = std::to_string(mode);

	if(user.length() + realname.length() + convertedMode.length() > 500)
		return false;

	string cmd = "USER " + user + " " + convertedMode + " * :"  + realname;
	cmd += cmdEnd;

	writeToServer((char *)cmd.c_str(), cmd.length());

	return true;
}

bool IRCParser::msgJOIN(string channel)
{
	if(channel.length() > 500)
		return false;

	string cmd = "JOIN ";
	cmd += channel;
	cmd += cmdEnd;

	writeToServer((char *)cmd.c_str(), cmd.length());

	return true;
}

bool IRCParser::msgJOIN(string channel, string key)
{
	if(channel.length() > 500)
		return false;

	string cmd = "JOIN ";
	cmd += channel + " " + key;
	cmd += cmdEnd;

	writeToServer((char *)cmd.c_str(), cmd.length());

	return true;
}

bool IRCParser::msgPRIVMSG(string target, string message)
{
	if(target.length() + message.length() > 500)
		return false;

	string cmd = "PRIVMSG ";
	cmd += target + " :" + message;
	cmd += cmdEnd;

	writeToServer((char *)cmd.c_str(), cmd.length());

	return true;
}

bool IRCParser::rspPRIVMSG(string cmd)
{
	//get sender
	int senderStart = 1, senderEnd = 0;
	senderEnd = cmd.find_first_of("!");
	if(senderEnd > 9 || senderEnd <= 1) //nickname is at most 9 characters
		return false;
	string sender = cmd.substr(1, senderEnd - 1);

	//get message
	int msgStart = cmd.find_last_of(":");
	if(msgStart <= 1 || cmd.length() - msgStart - 3 <= 0)
		return false;
	string msg = cmd.substr(msgStart + 1, cmd.length() - msgStart - 3);

	onMsgReceived(sender, msg);

	return true;
}

bool IRCParser::rspJOIN(string cmd)
{
	//find out channel name
	int chNameStart = cmd.find_first_of("#", 0);
	if(chNameStart <= 1)
		return false;
	joinedChannel = cmd.substr(chNameStart, cmd.length() - 2 - chNameStart);

	printf("joined channel %s\n", joinedChannel.c_str());

	return true;
}

string IRCParser::getChannel()
{
	return joinedChannel;
}





