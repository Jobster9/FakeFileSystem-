#pragma once
#include <iostream>
#include "FileSystem.h"
#include "FileSystemException.h"
#include "FSUtils.h"

using namespace std;

class Command
{
public:
	virtual void execute(const vector<string>& args) = 0;
	virtual int getArgNum() const = 0;
	virtual string getCommandName() const = 0;
	virtual string getParameters() const = 0;
	virtual string getDescription() const = 0;

};

//Display
class Dir : public Command 
{

public:
	int getArgNum() const { return 0; };
	string getCommandName() const { return "dir"; }
	string getParameters() const { return "none"; }
	string getDescription() const { return "Display contents of current directory"; }

	void execute(const vector<string>& args)
	{

		FileSystem* fs = FileSystem::getInstance();
		
		fs->getCurrentDir()->displayContents();

	}
};

//Sort directory contents by size
class SortBySize : public Command
{

public:
	int getArgNum() const { return 0; };
	string getCommandName() const { return "sortsize"; }
	string getParameters() const { return "none"; }
	string getDescription() const { return "Sort directory contents by file size (ascending)"; }

	void execute(const vector<string>& args)
	{

		FileSystem* fs = FileSystem::getInstance();

		fs->getCurrentDir()->sortBySize();
	}

};

//Sort directory contents by name
class SortByName : public Command
{

public:
	int getArgNum() const { return 0; };
	string getCommandName() const { return "sortname"; }
	string getParameters() const { return "none"; }
	string getDescription() const { return "Sort directory contents alphabetically by name"; }

	void execute(const vector<string>& args)
	{
		FileSystem* fs = FileSystem::getInstance();

		fs->getCurrentDir()->sortByName();

	}

};

//Find & enter Directory 
class Cd : public Command
{

public:
	int getArgNum() const { return 1; };
	string getCommandName() const { return "cd"; }
	string getParameters() const { return "<directory_name> or .."; }
	string getDescription() const { return "Change to specified directory or parent (..)"; }

	void execute(const vector<string>& args)
	{
		string itemName = args.at(0);
		FileSystem* fs = FileSystem::getInstance();

		if (itemName == "..") 
		{
			if (fs->getCurrentDir() == fs->getRootDir()) 
			{
				throw FileSystemException(FileSystemException::TRANSCEND_ROOT_DIR);
			}
			else
			{
				fs->moveToParentDirectory();
			}
		}
		else
		{
			FileItem* item = fs->getCurrentDir()->searchFolder(itemName);
			
			Directory* subDir = dynamic_cast<Directory*>(item);
			if (subDir != nullptr)
			{
				fs->setCurrentDir(subDir);
			}
			else
			{
				throw FileSystemException(FileSystemException::DIR_NOT_FOUND);
			}
		}		
	}

};

//Make Directory
class Mkdir : public Command 
{

public:
	int getArgNum() const { return 1; };
	string getCommandName() const { return "mkdir"; }
	string getParameters() const { return "<directory_name>"; }
	string getDescription() const { return "Create a new directory with specified name"; }

	void execute(const vector<string>& args)
	{
		string name = args.at(0);
		FileSystem* fs = FileSystem::getInstance();

		FileItem* item = fs->getCurrentDir()->searchFolder(name);

		if (item != nullptr)
		{
			throw FileSystemException(FileSystemException::DUPLICATE_ITEM_NAME);
		}

		string path = fs->getCurrentDir()->getPath();
		string newPath = FSUtils::updatePath(path, name);

		Directory* d1 = new Directory(name, FSUtils::getCurrentTime(),fs->getCurrentDir(), newPath );
		fs->getCurrentDir()->getDirContents().addItem(d1);

	}
	
};

//Make File
class Mkfile : public Command
{

public:
	int getArgNum() const { return 1; };
	string getCommandName() const { return "mkfile"; }
	string getParameters() const { return "<file_name>"; }
	string getDescription() const { return "Create a new file with specified name and random size"; }

	void execute(const vector<string>& args)
	{
		string name = args.at(0);
		FileSystem* fs = FileSystem::getInstance();

		FileItem* item = fs->getCurrentDir()->searchFolder(name);

		if (item != nullptr)
		{
			throw FileSystemException(FileSystemException::DUPLICATE_ITEM_NAME);
		}

		File* f1 = new File(name, FSUtils::getCurrentTime(), FSUtils::generateFileSize());
		fs->getCurrentDir()->getDirContents().addItem(f1);

	}

};


//Delete Item
class Del : public Command
{

public:
	int getArgNum() const { return 1; };
	string getCommandName() const { return "del"; }
	string getParameters() const { return "<item_name>"; }
	string getDescription() const { return "Delete specified file or directory"; }

	void execute(const vector<string>& args)
	{
		string name = args.at(0);
		FileSystem* fs = FileSystem::getInstance();

		FileItem* item = fs->getCurrentDir()->searchFolder(name);

		if (item == nullptr)
		{
			throw FileSystemException(FileSystemException::ITEM_NOT_FOUND);
		}

		fs->getCurrentDir()->getDirContents().removeItem(item);

	}

};


//Exit Application
class Exit : public Command
{

public:
	int getArgNum() const { return 0; };
	string getCommandName() const { return "exit"; }
	string getParameters() const { return "none"; }
	string getDescription() const { return "Exit the file system application"; }

	void execute(const vector<string>& args)
	{
		FileSystem* fs = FileSystem::getInstance();

		FileItem* item = fs->getRootDir();
		delete item;
	}

};


//List of Commands 
class Help: public Command
{
public:

	int getArgNum() const { return 0; };
	string getCommandName() const { return "help"; }
	string getParameters() const { return "none"; }
	string getDescription() const { return "Display list of available commands with descriptions"; }

	//Special case, defined in Menu.cpp due to class access requirements
	void execute(const vector<string>& args) override;
};

//Rename Item
class Rename : public Command
{

public:
	int getArgNum() const { return 2; };
	string getCommandName() const { return "rename"; }
	string getParameters() const { return "<current_name> <new_name>"; }
	string getDescription() const { return "Rename a file or directory"; }

	void execute(const vector<string>& args)
	{
		string oldName = args.at(0);
		string newName = args.at(1);
		FileSystem* fs = FileSystem::getInstance();

		FileItem* item = fs->getCurrentDir()->searchFolder(oldName);

		if (item == nullptr)
		{
			throw FileSystemException(FileSystemException::ITEM_NOT_FOUND);
		}

		FileItem* duplicateName = fs->getCurrentDir()->searchFolder(newName);

		if (duplicateName)
		{
			throw FileSystemException(FileSystemException::DUPLICATE_ITEM_NAME);
		}

		item->rename(newName);
	}

};

