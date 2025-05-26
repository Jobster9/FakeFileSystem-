#pragma once
#include <iostream>
#include <map>
#include "Command.h"
#include "FileSystem.h"


using namespace std;

class Menu
{
	public:
		static void runMenuInterface();
		static string promptUserForCommand();
		static void processCommand(string& command);
        static const map<string, shared_ptr<Command>>& getCommands() { return commands; }
	private:
		static map<string, shared_ptr<Command>> commands;

		//Command names 
        static const string DIR_COMMAND;
        static const string MKDIR_COMMAND;
        static const string MKFILE_COMMAND;
        static const string EXIT_COMMAND;
        static const string CD_COMMAND;
        static const string DEL_COMMAND;
        static const string SORTNAME_COMMAND;
        static const string SORTSIZE_COMMAND;
        static const string HELP_COMMAND;
        static const string RENAME_COMMAND;
};