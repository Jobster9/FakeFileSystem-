
#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <filesystem>// file system needs cpp standard 17 or above.  This is enabled in this project, but if you recreated from scratch, set -std=c++17 flags
#include "Menu.h"
#include "CustomVector.h"
#include "FSBuilder.h"



using namespace std;

// C++ entry point
int main()
{
#ifdef _DEBUG
  // make sure we are checking for memory leaks when the application ends, but only in the _DEBUG variant
    //  _CrtSetBreakAlloc(87);
  _onexit(_CrtDumpMemoryLeaks);
#endif

 FSBuilder::initialiseFileSystem();
 Menu::runMenuInterface();

  return 0;
}
