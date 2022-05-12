#ifndef FILENOTFOUNDEXCEPTION_H_
#define FILENOTFOUNDEXCEPTION_H_

#include <string>

using namespace std;

class FileNotFoundException
{
public:
  string what();
};

string FileNotFoundException::what()
{
  return "Could not open the file";
}

#endif