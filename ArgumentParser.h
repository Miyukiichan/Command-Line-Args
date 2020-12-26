/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#pragma once

#include <string>
#include <map>

typedef bool (*pfunc)(std::string);
typedef std::map<std::string, pfunc> funcMap;

class ArgumentParser
{
public:
  static bool parseArguments(int argc, char *argv[]);
  static void registerArgument(std::string argument, pfunc func);

protected:
  inline static funcMap argFuncs;
};