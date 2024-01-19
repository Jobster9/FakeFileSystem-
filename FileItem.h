#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <filesystem>
#include "FSUtils.h"


using namespace std;

class FileItem
{
public:

	FileItem(string name, tm timestamp);
	virtual ~FileItem() {};
	virtual void display() const = 0;
	bool operator==(const string& other) const;
	bool compareNamesAlphabetically(FileItem* other) const;
	void rename(string& newName);
	
private:
	string name;
	tm timestamp;
protected:
	inline string getName() const { return name; }
	inline tm getTimeStamp() const { return timestamp; }
};



