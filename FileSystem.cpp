#include "FileSystem.h"
//mutex part inspired from usage of mutex with lockguard for a thread safe singleton : https://www.quora.com/How-can-you-implement-a-thread-safe-singleton-class-in-C

FileSystem* FileSystem::instance = NULL;
mutex FileSystem::mutex;

FileSystem* FileSystem::getInstance() 
{
    if (!instance)
    {
        lock_guard<std::mutex> lock(mutex);

        if (!instance)
        {
            instance = new FileSystem();
        }
    }

    return instance;
}

void FileSystem::moveToParentDirectory()
{
    currentDir = currentDir->getParent(); 
}

