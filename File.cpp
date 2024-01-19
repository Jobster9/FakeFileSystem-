#include "File.h"


File::File(string fileName,tm timestamp, int fileSize) : FileItem(fileName,timestamp), fileSize(fileSize) {}

File::~File(){}

void File::display() const
{
    tm timestamp = getTimeStamp();
    string name = getName();

    int nameWidth = 40;
    int sizeWidth = 10; 

    cout << setfill(' ') << setw(2) << timestamp.tm_mday << "/"
        << setfill(' ') << setw(2) << (timestamp.tm_mon + 1) << "/"
        << setw(4) << (timestamp.tm_year + 1900)
        << " " << setfill(' ') << setw(2) << timestamp.tm_hour << ":"
        << setfill(' ') << setw(2) << timestamp.tm_min << " File: "
        << left << setw(nameWidth) << name 
        << "Size : " << right << setw(sizeWidth) << fileSize << "kb" << endl;
}

