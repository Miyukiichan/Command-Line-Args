/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include <iostream>
#include <set>

#include "ArgumentParser.h"

//TODO Have n number of argument values per option

bool ArgumentParser::parseArguments(int argc, char *argv[]) {
  std::set<std::string> usedArgs;
  for (int i = 1; i < argc; i += 2) {
    std::string argName = argv[i];
    if (argFuncs.count(argName) == 0) {
      std::cout << "Unrecognised argument " << argName << std::endl;
      return false;
    }
    if (usedArgs.find(argName) != usedArgs.end()) {
      std::cout << "Argument \"" << argName << "\" used multiple times" << std::endl;
      return false;
    }
    std::string argValue = "";
    if (i + 1 < argc) {
      std::string tmp = argv[i + 1];
      if (argFuncs.count(tmp) == 0)
        argValue = tmp;
    }
    if (argValue.empty()) {
      std::cout << "No parameter given for " << argName << std::endl;
      return false;
    }
    pfunc f = argFuncs[argName];
    if (!(*f)(argValue)) return false;
    usedArgs.insert(argName);
  }
  return true;
}

void ArgumentParser::registerArgument(std::string argument, pfunc func) {
  argFuncs.emplace(argument, func);
}

