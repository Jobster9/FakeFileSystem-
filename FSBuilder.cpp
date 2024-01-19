#include "FSBuilder.h"

void FSBuilder::initialiseFileSystem()
{
    FileSystem* fs = FileSystem::getInstance();
    Directory* rootDir = FSBuilder::createRootDirectory();
    fs->setRootDir(rootDir);
    fs->setCurrentDir(rootDir);
    FSBuilder::enumerateContents(rootDir);
    cout << "Initialisation Complete.." << endl;
}

Directory* FSBuilder::createRootDirectory()
{
    string path = "."; // Root directory
    auto last_write_time = filesystem::last_write_time(path);
    tm timestamp = FSUtils::convertTime(last_write_time);
    string name = filesystem::path(path).filename().string();

    return new Directory(name, timestamp, nullptr, path);
}


void FSBuilder::enumerateContents(Directory* dir)
{
    const string path = dir->getPath();

    for (const filesystem::directory_entry& item : filesystem::directory_iterator(path))
    {
        string name = item.path().filename().string();
        tm timestamp = FSUtils::convertTime(item.last_write_time());
        string currentPath = item.path().string();

        if (item.is_directory())
        {
            Directory* subDirectory = new Directory(name, timestamp, dir, currentPath);
            dir->getDirContents().addItem(subDirectory);
            _CrtCheckMemory();
            FSBuilder::enumerateContents(subDirectory);
        }
        else
        {
            __int64 filesize = item.file_size();
            File* file = new File(name, timestamp, filesize);
            dir->getDirContents().addItem(file);
        }
    }
}