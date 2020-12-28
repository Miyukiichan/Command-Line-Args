/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#pragma once

#include <string>
#include <map>
#include <vector>

/*Callbacks must take a string as an argument and return a boolean*/
typedef bool (*pfunc)(std::string);
typedef std::map<std::string, pfunc> funcMap;

/*Callbacks for list arguments take a vector of strings as an argument and return a boolean*/
typedef bool (*pfuncList)(std::vector<std::string>);
typedef std::map<std::string, pfuncList> funcListMap;

class ArgumentParser
{
public:
  static bool parseArguments(int argc, char *argv[]);
  static std::string quote(std::string str);
  static std::string quote(double str);

protected:
  /*Internal argument function map*/
  inline static funcMap argFuncs;
  inline static std::vector<std::string> arguments;
  inline static std::vector<pfunc> functions;
  /*Internal list argument function map*/
  inline static funcListMap argListFuncs;
  inline static std::vector<std::string> listArguments;
  inline static std::vector<pfuncList> listFunctions;

  static bool Init();

private:
  template <class T>
  static bool checkAndRegisterArguments(std::vector<std::string> args, std::vector<T> funcs, std::map<std::string, T> &functionMap);
};