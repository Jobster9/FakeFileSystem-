#include "Directory.h"


Directory::Directory(string dirName,tm timestamp,Directory* parent,string path) : FileItem(dirName,timestamp), parent(parent), path(path) {}

Directory::~Directory() 
{
    while (!contents.isEmpty()) {
        FileItem* item = contents[0]; 
        contents.removeItem(item);                      
    }
}

void Directory::display() const
{ 
  tm timestamp = getTimeStamp();
  string name = getName();
  cout <<timestamp.tm_mday<<"/"<<(timestamp.tm_mon + 1)<<"/"<<(timestamp.tm_year + 1900)
  <<"  "<< timestamp.tm_hour<<":"<< timestamp.tm_min<< " <DIR> " <<name<< endl;

}

void Directory::displayContents() const
{
    for (FileItem* item : contents)
    {
            item->display();       
    }
}


FileItem* Directory::searchFolder(const string& itemName) const
{
    for (FileItem* item : contents) 
    {
        if (*item == itemName) 
        {
            return item;
        }
    }

    return nullptr;

}

void Directory::sortBySize()
{
    int subDirIndex = arrangeSubDirectories();

    int n = contents.Size();

    bool noSwap = false;

    while (!noSwap)
    {
        noSwap = true;
        for (size_t i = subDirIndex; i < n - 1; i++)
        {
            File* fileA = dynamic_cast<File*>(contents[i]);
            File* fileB = dynamic_cast<File*>(contents[i + 1]);

            if ((fileA && fileB) && *fileA > *fileB) 
            {
                contents.swap(i, i + 1);
                noSwap = false;
            }
        }
    }
    
}

void Directory::sortByName()
{

    int n = contents.Size();

    bool noSwap = false;

    while (!noSwap)
    {
        noSwap = true;
        for (size_t i = 0; i < n - 1; i++)
        {
            FileItem* itemA = contents[i];
            FileItem* itemB = contents[i + 1];
            if (itemA->compareNamesAlphabetically(itemB))
            {
                contents.swap(i, i + 1);
                noSwap = false;
            }
        }
    }
}

int Directory::arrangeSubDirectories() {
    
    size_t nextDirIndex = 0;
    size_t currentIndex = 0;  
    
    for (FileItem* item : contents)
    {
        if (dynamic_cast<Directory*>(item)) 
        {
            if (currentIndex != nextDirIndex) 
            {
                contents.swap(currentIndex, nextDirIndex);
            }            
            nextDirIndex++;  // Increment the index for the next directory
        }
        currentIndex++;
    }

    return nextDirIndex;   
}