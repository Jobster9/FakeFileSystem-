#pragma once
#include "FileItem.h"
#include "File.h"
#include "CustomVector.h"

class Directory : public FileItem
{
public:
	Directory(string dirName,tm timestamp,Directory* parent,string filepath);
	~Directory();
	void display() const;
	void displayContents() const;
	void sortBySize();
	void sortByName();
	CustomVector<FileItem* >& getDirContents() { return contents; }
	string getPath() const { return path; }
	FileItem* searchFolder(const string& itemName) const;
	Directory* getParent() const { return parent; }
	
private:
	int arrangeSubDirectories();
	CustomVector<FileItem* > contents;
	string path;
	Directory* parent;
};

