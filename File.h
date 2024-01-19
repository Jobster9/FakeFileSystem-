#pragma once
#include "FileItem.h"

class File : public FileItem
{
public:
	File(string fileName,tm timestamp, int fileSize);
	~File();
	void display() const;
	int getFileSize() const { return fileSize; }
	inline bool operator>(const File& other) const { return fileSize > other.fileSize; }

private:
	int fileSize;
};

