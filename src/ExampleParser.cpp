/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include <sys/stat.h>
#include <iostream>

#include "ExampleParser.h"

void ExampleParser::Init()
{
  inputFile = "";
  outputFile = "output.txt";
  multiplier = 1;
  registerArgument("-i", setInputFile);
  registerArgument("-o", setOutputFile);
  registerArgument("-m", setMultiplier);
}

bool ExampleParser::setInputFile(std::string filename)
{
  struct stat buffer;
  if (stat(filename.c_str(), &buffer) != 0)
  {
    std::cout << "Input file \"" << filename << "\" does not exist" << std::endl;
    return false;
  }
  inputFile = filename;
  return true;
}

bool ExampleParser::setOutputFile(std::string filename)
{
  outputFile = filename;
  return true;
}

bool ExampleParser::setMultiplier(std::string mult)
{
  double temp;
  try
  {
    temp = stod(mult);
  }
  catch (const std::invalid_argument &ia)
  {
    std::cout << "Invalid Multiplier \"" << mult << "\"" << std::endl;
    return false;
  }
  multiplier = temp;
  return true;
}