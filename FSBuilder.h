#pragma once
#include "FileSystem.h"
#include "FSUtils.h"

class FSBuilder
{
public:

	static void initialiseFileSystem();
	static void enumerateContents(Directory* dir);
	static Directory* createRootDirectory();

private:
	FSBuilder(){};

};

