/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include <iostream>
#include <set>

#include "ArgumentParser.h"

/*Main parsing function returns true on success and false on any failure. As soon as it fails, it stops*/
bool ArgumentParser::parseArguments(int argc, char *argv[])
{
  std::set<std::string> usedArgs; //Keep track of already used arguments
  for (int i = 1; i < argc; i += 2)
  {
    std::string argName = argv[i];
    //Check that argument has been registered
    if (argFuncs.count(argName) == 0)
    {
      std::cout << "Unrecognised argument " << argName << std::endl;
      return false;
    }
    //Check that argument has not been used previously. No duplicates allowed
    if (usedArgs.find(argName) != usedArgs.end())
    {
      std::cout << "Argument \"" << argName << "\" used multiple times" << std::endl;
      return false;
    }
    std::string argValue = "";
    //Check that the next argument is not another option. If not, set that as the value, otherwise, the value is empty
    if (i + 1 < argc)
    {
      std::string tmp = argv[i + 1];
      if (argFuncs.count(tmp) == 0)
        argValue = tmp;
    }
    //No value passed for that option
    if (argValue.empty())
    {
      std::cout << "No parameter given for " << argName << std::endl;
      return false;
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
void ArgumentParser::registerArgument(std::string argument, pfunc func)
{
  argFuncs.emplace(argument, func);
}
