/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#pragma once

#include <string>
#include <map>
#include <vector>

/*Callbacks must take a string as an argument and return a boolean*/
typedef bool (*pfunc)(std::string);
typedef std::map<std::string, pfunc> funcMap;

class ArgumentParser
{
public:
  static bool parseArguments(int argc, char *argv[]);
  static bool registerArgument(std::string argument, pfunc func);
  static std::string quote(std::string str);
  static std::string quote(double str);

protected:
  /*Internal argument function map*/
  inline static funcMap argFuncs;
  inline static std::vector<std::string> arguments;
  inline static std::vector<pfunc> functions;
  static bool Init();
};