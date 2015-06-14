#include "stdafx.h"
#include "Console.h"
#include <iostream>
#include <algorithm>
#include <regex>
#include <sstream>

Console::Console()		
{
	nrOfCommands = 7;
	const char* comm[] = { "cd", "mkdir", "del", "ls", "create", "count", "help", "exit" };

	for (int i = 0; i < nrOfCommands; ++i)
		commands.push_back(std::string(comm[i]));
}

void Console::Run()
{
	const std::string onePPattern = "(\\s)*(\\w)+(\\s)+(\\S)+(\\s)*";
	const std::string noPPattern = "(\\s)*(\\w)+(\\s)*";
	std::string line;			

	std::cout << "*** Console Simulator (ver. 0.1) ***\n" << std::endl;
	while ( true )
	{
		try
		{
			std::cout << dirTree.currentDirectoryPath() << '>';
			getline(std::cin, line);			
			if (std::regex_match(line, std::regex(noPPattern)) )
			{
				line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
				executeCommand(line);

			}
			else if (std::regex_match(line, std::regex(onePPattern)))
			{					
				std::istringstream iStream(line);
				std::string command, param;
				iStream >> command >> param;
				executeCommand(command, param, "");
			}
			else
				if (!line.empty())
					std::cout << "Invalid input\n" << std::endl;			
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

void Console::executeCommand(std::string &command, const std::string& path, const std::string &otherInfo )
{			
	int commandIndex = -1;

	for (int cm_i = 0; cm_i < nrOfCommands; ++cm_i)
		if (command == commands[cm_i])
			commandIndex = cm_i;

	switch (commandIndex)
	{
	case -1:
		throw std::invalid_argument("Invalid command");
		break;
	case 0: 
		dirTree.changeDirectory(path);
		break;
	case 1: 
		dirTree.makeDirectory(path);
		break;
	case 2: 
		dirTree.deleteEntity(path);
		break;
	case 3: 
		std::cout << dirTree.getDirectoryString(path) << std::endl;
		break;
	case 4: 
		dirTree.createFile(path, otherInfo);
		break;
	case 5:
		std::cout << dirTree.count(path) << " items." << std::endl;
		break;
	default: 
		break;
	}
}

void Console::executeCommand(std::string& command)
{
	if (command == "ls")
		std::cout << dirTree.getDirectoryString(".") << std::endl;
	else if (command == "help")	
		for (int i = 0; i < nrOfCommands; ++i)
			std::cout << commands[i] << std::endl;	
	else if (command == "exit")	
		exit(EXIT_SUCCESS);	
	else
		std::cout << "Invalid command" << std::endl;
}

// ...