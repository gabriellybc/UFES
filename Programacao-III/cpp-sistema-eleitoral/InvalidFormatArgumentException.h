#ifndef INVALIDFORMATARGUMENTEXCEPTION_H_
#define INVALIDFORMATARGUMENTEXCEPTION_H_

#include <string>

using namespace std;

class InvalidFormatArgumentException
{
public:
  string what();
};

string InvalidFormatArgumentException::what()
{
  return "Invalid input data format";
}

#endif