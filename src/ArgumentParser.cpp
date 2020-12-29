/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include <iostream>
#include <set>

#include "ArgumentParser.h"

/*Main parsing function returns true on success and false on any failure. As soon as it fails, it stops*/
bool ArgumentParser::parseArguments(int argc, char *argv[])
{
  std::set<std::string> usedArgs; //Keep track of already used arguments
  bool hasDefaultArgument = argFuncs.count("") == 0 || argListFuncs.count("") == 0;
  for (int i = 1; i < argc; i += 2)
  {
    std::string argName = argv[i];
    if (argName == helperOption)
    {
      printHelpMessage();
      return false;
    }
    std::vector<std::string> argValues;
    bool isDefaultArgument = false;
    //Check that argument has been registered
    if (argFuncs.count(argName) == 0 && argListFuncs.count(argName) == 0)
    {
      //Check if a default argument has been registered or if it has been used already
      if (!hasDefaultArgument || usedArgs.find("") != usedArgs.end())
      {
        std::cout << "Unrecognised argument " << quote(argName) << std::endl;
        return false;
      }
      isDefaultArgument = true;
      argName = "";
    }
    bool isListValue = argListFuncs.count(argName) > 0;
    //Check that argument has not been used previously. No duplicates allowed
    if (usedArgs.find(argName) != usedArgs.end())
    {
      std::cout << "Argument " << quote(argName) << " used multiple times" << std::endl;
      return false;
    }
    int j = isDefaultArgument ? i : i + 1;
    for (j; j < argc; j++)
    {
      std::string temp = argv[j];
      if (argValues.size() > 0 && !isListValue)
        break;
      if (temp == argName || (argFuncs.count(temp) == 0 && argListFuncs.count(temp) == 0))
        argValues.push_back(temp);
      else
        break;
    }
    i = j - 2;
    if (argValues.empty())
    {
      std::cout << "No parameter given for " << quote(argName) << std::endl;
      return false;
    }
    if (!isListValue)
    {
      //Get the respective callback for the registered argument and call it
      pfunc f = argFuncs[argName];
      if (!(*f)(argValues[0]))
        return false;
    }
    else
    {
      pfuncList f = argListFuncs[argName];
      if (!(*f)(argValues))
        return false;
    }
    usedArgs.insert(argName); //We've now used this argument
  }
  return true;
}

void ArgumentParser::printDescriptions(std::string sectionMessage, std::map<std::string, std::string> descMap, bool printNewLine)
{
  if (descMap.size() == 0)
    return;
  std::cout << sectionMessage << std::endl;
  for (auto const &entry : descMap)
  {
    std::cout << entry.first << " - " << entry.second << std::endl;
  }
  if (printNewLine)
    std::cout << std::endl;
}

void ArgumentParser::printHelpMessage()
{
  if (descriptionPrinter)
  {
    descriptionPrinter();
    return;
  }
  printDescriptions("Arguments:", descriptionMap);
  printDescriptions("List Arguments:", listDescriptionMap, false);
}

bool ArgumentParser::Init()
{
  for (std::string str : arguments)
  {
    for (std::string listStr : listArguments)
    {
      if (str == listStr)
      {
        std::cout << "Programmer error! Argument used for regular and list registration lists" << std::endl;
        return false;
      }
    }
  }
  return checkAndRegisterArguments(arguments, functions, argFuncs) &&
         checkAndRegisterArguments(listArguments, listFunctions, argListFuncs) &&
         registerDescriptions(arguments, descriptions, descriptionMap) &&
         registerDescriptions(listArguments, listDescriptions, listDescriptionMap);
}

template <class T>
bool ArgumentParser::checkAndRegisterArguments(std::vector<std::string> args, std::vector<T> funcs, std::map<std::string, T> &functionMap)
{
  if (args.size() != funcs.size())
  {
    std::cout << "Programmer error! Argument and callback list count are not equal" << std::endl;
    return false;
  }
  for (int i = 0; i < args.size(); i++)
  {
    std::string argument = args[i];
    T func = funcs[i];
    if (functionMap.count(argument) > 0)
    {
      argument = argument.empty() ? defaultArgumentDescription : argument;
      std::cout << "Programmer error! " << quote(argument) << " already registered" << std::endl;
      return false;
    }
    functionMap.emplace(argument, func);
  }
  return true;
}

bool ArgumentParser::registerDescriptions(std::vector<std::string> args, std::vector<std::string> descs, std::map<std::string, std::string> &descMap)
{
  if (descs.size() > args.size())
  {
    std::cout << "Programmer Error! Too many descriptions registered for arguments" << std::endl;
    return false;
  }
  const std::string noDescription = defaultDescription;
  for (int i = 0; i < args.size(); i++)
  {
    std::string arg = args[i];
    arg = arg.empty() ? defaultArgumentDescription : arg;
    std::string desc = (i < descs.size()) ? descs[i] : noDescription;
    desc = desc.empty() ? noDescription : desc;
    descMap.emplace(arg, desc);
  }
}

std::string ArgumentParser::quote(std::string str)
{
  return "\"" + str + "\"";
}

std::string ArgumentParser::quote(double str)
{
  return quote(std::to_string(str));
}