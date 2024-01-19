#include "FSUtils.h"

tm FSUtils::convertTime(const filesystem::file_time_type& timestamp)
{
    using namespace chrono;  // just for this function, use chrono to save us prefixing chrono:: everywhere
    system_clock::time_point delta = time_point_cast<system_clock::duration>(timestamp - filesystem::file_time_type::clock::now() + system_clock::now());
    time_t conversion = system_clock::to_time_t(delta);

    tm result;
    localtime_s(&result, &conversion);
    return result;
}

tm FSUtils::getCurrentTime() {

    using namespace chrono;
    time_t now = system_clock::to_time_t(system_clock::now());
    tm result;
    localtime_s(&result, &now);
    return result;
}

int FSUtils::generateFileSize()
{
    return rand() % MAX_FILE_SIZE;
}

//Code for splitStrings method is inspired from: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
// Allowed me to understand stringstream,tokenising & adapt for possible multiple arguments to a command

vector<string> FSUtils::splitString(string& str, char delim)
{
    vector<string> tokens;

    if (str.empty()) return tokens;

    string currentToken;

    stringstream ss(str);

    while (getline(ss, currentToken, delim))
    {
        tokens.push_back(currentToken);
    }

    return tokens;
}

string FSUtils::updatePath(string& currentPath,string& dirName)
{
    return currentPath + "\\" + dirName;
}

