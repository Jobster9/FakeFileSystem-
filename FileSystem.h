#pragma once
#include <iostream>
#include <chrono>
#include <filesystem>
#include <mutex>
#include "Directory.h"
#include "File.h"


using namespace std;

class FileSystem
{
	public:

		static FileSystem* getInstance();

		FileSystem(FileSystem const&) = delete;
		void operator=(FileSystem const&) = delete;

		Directory* getRootDir() const { return rootDir; };
		void setRootDir(Directory* dir) { rootDir = dir; };
		Directory* getCurrentDir() const { return currentDir; };
		void setCurrentDir(Directory* newDir) { currentDir = newDir; }
		void moveToParentDirectory();

	private:
		static FileSystem* instance;
		static mutex mutex;
		FileSystem() {};
		Directory* rootDir;
		Directory* currentDir;
		string name;
	
};


