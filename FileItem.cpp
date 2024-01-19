#include "FileItem.h"

//Iterator tolower method code inspired from: https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case


FileItem::FileItem(string name,tm timestamp) : name(name), timestamp(timestamp) {}


void FileItem::rename(string& newName) 
{
	name = newName;
}

bool FileItem::operator==(const string& other) const
{ 
	return name == other ? true : false; 
}

bool FileItem::compareNamesAlphabetically(FileItem* other) const
{
	string otherName = other->getName();
	string objectName = name;

	transform(otherName.begin(), otherName.end(), otherName.begin(),
		[](unsigned char c) { return tolower(c); });

	transform(objectName.begin(), objectName.end(), objectName.begin(),
		[](unsigned char c) { return tolower(c); });

	

	return name > otherName ? true : false;
}