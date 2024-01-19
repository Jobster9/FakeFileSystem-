#pragma once
#include <iostream>
#include "FileSystem.h"
#include "FileSystemException.h"

using namespace std;

class Command
{
public:
	virtual void execute(const vector<string>& args) = 0;
	virtual int getArgNum() = 0;
};

//Display
class Dir : public Command 
{

public:
	int getArgNum() { return 0; };
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
	int getArgNum() { return 0; };
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
	int getArgNum() { return 0; };
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
	int getArgNum() { return 1; };

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
	int getArgNum() { return 1; };

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
		tm timestamp = FSUtils::getCurrentTime();
		Directory* d1 = new Directory(name, timestamp,fs->getCurrentDir(), newPath );
		fs->getCurrentDir()->getDirContents().addItem(d1);

	}
	
};

//Make File
class Mkfile : public Command
{

public:
	int getArgNum() { return 1; };

	void execute(const vector<string>& args)
	{
		string name = args.at(0);
		FileSystem* fs = FileSystem::getInstance();

		FileItem* item = fs->getCurrentDir()->searchFolder(name);

		if (item != nullptr)
		{
			throw FileSystemException(FileSystemException::DUPLICATE_ITEM_NAME);
		}

		tm timestamp = FSUtils::getCurrentTime();
		File* f1 = new File(name, timestamp, FSUtils::generateFileSize());
		fs->getCurrentDir()->getDirContents().addItem(f1);

	}

};


//Delete Item
class Del : public Command
{

public:
	int getArgNum() { return 1; };

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
	int getArgNum() { return 0; };

	void execute(const vector<string>& args)
	{
		FileSystem* fs = FileSystem::getInstance();

		FileItem* item = fs->getRootDir();
		delete item;
	}

};


//More Commands 
class MoreCommands: public Command
{

public:
	int getArgNum() { return 0; };

	void execute(const vector<string>& args)
	{

		cout << "More Commands: " << std::endl;
		cout << "Name: rename | Parameters: current name, new name | Description: rename a file or directory.|" << std::endl;

	}
};

//Rename Item
class Rename : public Command
{

public:
	int getArgNum() { return 2; };

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

