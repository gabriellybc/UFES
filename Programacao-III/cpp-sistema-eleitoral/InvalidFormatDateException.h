#ifndef INVALIDFORMATDATEEXCEPTION_H_
#define INVALIDFORMATDATEEXCEPTION_H_

#include <string>

using namespace std;

class InvalidFormatDateException
{
public:
  string what();
};

string InvalidFormatDateException::what()
{
  return "Invalid date according to format";
}

#endif