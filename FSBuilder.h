#pragma once
#include "FileSystem.h"

class FSBuilder
{
public:

	static void initialiseFileSystem();
	static void enumerateContents(Directory* dir);
	static Directory* createRootDirectory();

private:
	FSBuilder(){};

};

