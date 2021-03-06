/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>

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
  template <class T>
  static bool existsInSet(T arg, std::set<T> list);

protected:
  /*Internal argument function map*/
  inline static funcMap argFuncs;
  inline static std::vector<std::string> arguments;
  inline static std::vector<pfunc> functions;
  inline static std::vector<std::string> descriptions;
  inline static std::map<std::string, std::string> descriptionMap;

  /*Internal list argument function map*/
  inline static funcListMap argListFuncs;
  inline static std::vector<std::string> listArguments;
  inline static std::vector<pfuncList> listFunctions;
  inline static std::vector<std::string> listDescriptions;
  inline static std::map<std::string, std::string> listDescriptionMap;

  static bool Init();
  static void printHelpMessage();
  inline static void (*descriptionPrinter)() = printHelpMessage; //Callback set to the default printing function

  /*User options*/
  inline static std::string helperOption = "--help"; // Option the user enters to receive the help message
  inline static std::string defaultDescription = "No Description";
  inline static std::string defaultArgumentDescription = "Default Argument"; // Displayed in lieu of empty string
  inline static bool allowEmptyArguments = false;                            // Eg ./parser.out -o -m 2 will not throw an error
  inline static bool allowDuplicateArguments = false;                        // Eg ./parser.out -o test -o test2 will not throw an error

private:
  template <class T>
  static bool checkAndRegisterArguments(std::vector<std::string> args, std::vector<T> funcs, std::map<std::string, T> &functionMap);
  static bool registerDescriptions(std::vector<std::string> args, std::vector<std::string> descs, std::map<std::string, std::string> &descMap);
  static void printDescriptions(std::string sectionMessage, std::map<std::string, std::string> descMap, bool printNewLine = true);
  static bool argumentExists(std::string arg);
};