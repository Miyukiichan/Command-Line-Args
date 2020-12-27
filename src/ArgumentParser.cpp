/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include <iostream>
#include <set>

#include "ArgumentParser.h"

/*Main parsing function returns true on success and false on any failure. As soon as it fails, it stops*/
bool ArgumentParser::parseArguments(int argc, char *argv[])
{
  std::set<std::string> usedArgs; //Keep track of already used arguments
  bool hasDefaultArgument = argFuncs.count("") == 0;
  for (int i = 1; i < argc; i += 2)
  {
    std::string argName = argv[i];
    std::string argValue = "";
    //Check that argument has been registered
    if (argFuncs.count(argName) == 0)
    {
      //Check if a default argument has been registered or if it has been used already
      if (hasDefaultArgument || usedArgs.find("") != usedArgs.end())
      {
        std::cout << "Unrecognised argument " << quote(argName) << std::endl;
        return false;
      }
      else
      {
        argValue = argName;
        argName = "";
        i--;
      }
    }
    if (argValue.empty())
    {
      //Check that argument has not been used previously. No duplicates allowed
      if (usedArgs.find(argName) != usedArgs.end())
      {
        std::cout << "Argument " << quote(argName) << " used multiple times" << std::endl;
        return false;
      }
      //Check that the next argument is not another option. If not, set that as the value, otherwise, the value is empty
      if (i + 1 < argc)
      {
        std::string tmp = argv[i + 1];
        if (tmp == argName || argFuncs.count(tmp) == 0)
          argValue = tmp;
      }
      //No value passed for that option
      if (argValue.empty())
      {
        std::cout << "No parameter given for " << quote(argName) << std::endl;
        return false;
      }
    }
    //Get the respective callback for the registered argument and call it
    pfunc f = argFuncs[argName];
    if (!(*f)(argValue))
      return false;
    usedArgs.insert(argName); //We've now used this argument
  }
  return true;
}

/*Wrapper function for adding the argument and callback to the internal map*/
bool ArgumentParser::registerArgument(std::string argument, pfunc func)
{
  if (argFuncs.count(argument) > 0)
  {
    argument = argument.empty() ? "Default Argument" : argument;
    std::cout << "Programmer error! " << quote(argument) << " already registered" << std::endl;
    return false;
  }
  argFuncs.emplace(argument, func);
  return true;
}

bool ArgumentParser::Init()
{
  if (arguments.size() != functions.size())
  {
    std::cout << "Programmer error! Argument and callback list count are not equal";
    return false;
  }
  for (int i = 0; i < arguments.size(); i++)
  {
    if (!registerArgument(arguments[i], functions[i]))
      return false;
  }
  return true;
}

std::string ArgumentParser::quote(std::string str)
{
  return "\"" + str + "\"";
}

std::string ArgumentParser::quote(double str)
{
  return quote(std::to_string(str));
}