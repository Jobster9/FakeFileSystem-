#pragma once
#include <iostream>

// design idea: https://peterforgacs.github.io/2017/06/25/Custom-C-Exceptions-For-Beginners/
// https://codereview.stackexchange.com/questions/157448/error-handling-class
//allowed me to better structure the command errors with a generic exception

using namespace std;

class FileSystemException : public exception 
{
public:

    enum ErrorType
    {
        COMMAND_NOT_FOUND,
        INVALID_ARGUMENTS,
        DUPLICATE_ITEM_NAME,
        DIR_NOT_FOUND,
        TRANSCEND_ROOT_DIR,
        ITEM_NOT_FOUND,
    };

    FileSystemException(ErrorType type) : message(getErrorMessage(type)) {};
    const string what() {return message;}


private:
    const string message;

    static string getErrorMessage(ErrorType type){
        switch (type) {
        case COMMAND_NOT_FOUND: return "Error: Command not found.";
        case INVALID_ARGUMENTS: return "Error: Invalid arguments provided.";
        case DUPLICATE_ITEM_NAME: return "Error: Item name already exists.";
        case DIR_NOT_FOUND: return "Error: Directory not found.";
        case TRANSCEND_ROOT_DIR: return "Error: Cannot access parent directory, current directory is root.";
        case ITEM_NOT_FOUND: return "Error: Item not found.";
         
        default: return "Error: Unknown error.";
        }
    }


};
