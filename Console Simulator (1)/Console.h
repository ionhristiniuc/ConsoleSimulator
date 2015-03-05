#pragma once

#include "DirectoryTree.h"
#include <string>
#include <deque>

class Console
{
public:
	Console();	
	void Run();
	void executeCommand(std::string &command, const std::string& path, const std::string &otherInfo);	
	void executeCommand(std::string &command );
private:
	DirectoryTree dirTree;
	std::deque< std::string> commands;
	int nrOfCommands;
};