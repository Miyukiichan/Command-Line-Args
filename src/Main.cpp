/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include <iostream>

#include "ExampleParser.h"

int main(int argc, char *argv[])
{
  ExampleParser::Init();
  if (!ExampleParser::parseArguments(argc, argv))
    return 1;
  std::cout << "Input file is \"" << ExampleParser::inputFile << "\"" << std::endl;
  std::cout << "Output file is \"" << ExampleParser::outputFile << "\"" << std::endl;
  std::cout << "Multiplier is \"" << ExampleParser::multiplier << "\"" << std::endl;
  return 0;
}