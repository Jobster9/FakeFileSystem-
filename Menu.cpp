#include "Menu.h"

//Source for Map traversal - https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key

const string Menu::DIR_COMMAND = "dir";
const string Menu::MKDIR_COMMAND = "mkdir";
const string Menu::MKFILE_COMMAND = "mkfile";
const string Menu::EXIT_COMMAND = "exit";
const string Menu::CD_COMMAND = "cd";
const string Menu::DEL_COMMAND = "del";
const string Menu::SORTNAME_COMMAND = "sortname";
const string Menu::SORTSIZE_COMMAND = "sortsize";
const string Menu::MORE_COMMANDS_COMMAND = "commands";
const string Menu::RENAME_COMMAND = "rename";


map<string, shared_ptr<Command>> Menu::commands =
{
	{ DIR_COMMAND, make_shared<Dir>()},
	{ SORTNAME_COMMAND, make_shared<SortByName>()},
	{ SORTSIZE_COMMAND, make_shared<SortBySize>()},
	{ CD_COMMAND, make_shared<Cd>()},
	{ MKDIR_COMMAND, make_shared<Mkdir>()},
	{ MKFILE_COMMAND, make_shared<Mkfile>()},
	{ DEL_COMMAND, make_shared<Del>()},
	{ EXIT_COMMAND, make_shared<Exit>()},
	{ MORE_COMMANDS_COMMAND, make_shared<MoreCommands>()},
	{ RENAME_COMMAND, make_shared<Rename>()},
	
		
};

void Menu::runMenuInterface() 
{
    bool exit = false;
    string command;
    while (!exit) 
    {
        command = promptUserForCommand();
        if (command == EXIT_COMMAND) 
        {
            exit = true;
        }
        try
        {
            processCommand(command);
        }
        catch (FileSystemException e) 
        {
            cout << e.what() << endl;

        }
    }
}

string Menu::promptUserForCommand()
{
    FileSystem* fs = FileSystem::getInstance();
    string input;
    cout << "\\" << fs->getCurrentDir()->getPath() << ":>";
    getline(cin, input);
    cout << endl;
    return input;
}

void Menu::processCommand(string& input) 
{
    string commandName;
    vector<string> arguments;

    if (!input.length())
    {
        throw FileSystemException(FileSystemException::COMMAND_NOT_FOUND);
    }

    arguments = FSUtils::splitString(input, ' ');

    auto key = commands.find(arguments[0]);
    bool isCommand = key != commands.end(); //equivalent C++17 check to Map.contains(key)

    if (!isCommand)
    {
        throw FileSystemException(FileSystemException::COMMAND_NOT_FOUND);
    }
    commandName = arguments[0];
    arguments.erase(arguments.begin());
    shared_ptr<Command> command = key->second;

    if (command->getArgNum() != arguments.size())
    {
        throw FileSystemException(FileSystemException::INVALID_ARGUMENTS);
    }

        command->execute(arguments);
}