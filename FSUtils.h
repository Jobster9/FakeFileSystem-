#pragma once
#include <iostream>
#include <chrono>
#include <filesystem>
#include <sstream>

using namespace std;

class FSUtils
{
public:
	static tm convertTime(const filesystem::file_time_type& timestamp);
	static tm getCurrentTime();
	static int generateFileSize();
	static vector<string> splitString(string& str, char delim);
	static string updatePath(string& currentPath, string& dirName);
private:
	FSUtils(){};
	const static int MAX_FILE_SIZE = 1000;
};