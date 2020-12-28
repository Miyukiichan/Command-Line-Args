/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include <iostream>

#include "ExampleParser.h"

int main(int argc, char *argv[])
{
  if (!ExampleParser::Initialize())
    return 1;
  if (!ExampleParser::parseArguments(argc, argv))
    return 1;
  std::cout << "Input file is " << ExampleParser::quote(ExampleParser::inputFile) << std::endl;
  std::cout << "Output file is " << ExampleParser::quote(ExampleParser::outputFile) << std::endl;
  std::cout << "Multiplier is " << ExampleParser::quote(ExampleParser::multiplier) << std::endl;
  std::cout << "Count is " << ExampleParser::quote(ExampleParser::count) << std::endl;
  std::cout << "OTHER Count is " << ExampleParser::quote(ExampleParser::other_count) << std::endl;
  return 0;
}