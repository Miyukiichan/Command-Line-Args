/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include <sys/stat.h>
#include <iostream>

#include "ExampleParser.h"

/*Standard init function to set default property values and register arguments*/
bool ExampleParser::Initialize()
{
  inputFile = "";
  outputFile = "output.txt";
  multiplier = 1;
  arguments = {"", "-o", "-m"};
  functions = {setInputFile, setOutputFile, setMultiplier};
  return Init();
}

/*Checks that the given input file exists before setting the property*/
bool ExampleParser::setInputFile(std::string filename)
{
  struct stat buffer;
  if (stat(filename.c_str(), &buffer) != 0)
  {
    std::cout << "Input file " << quote(filename) << " does not exist" << std::endl;
    return false;
  }
  inputFile = filename;
  return true;
}

/*Just sets the property. The output file need not exist*/
bool ExampleParser::setOutputFile(std::string filename)
{
  outputFile = filename;
  return true;
}

/*Performs a conversion from string to double. Catches any conversion error and prints an error message before returning false*/
bool ExampleParser::setMultiplier(std::string mult)
{
  double temp;
  try
  {
    temp = stod(mult);
  }
  catch (const std::invalid_argument &ia)
  {
    std::cout << "Invalid Multiplier " << quote(mult) << std::endl;
    return false;
  }
  multiplier = temp;
  return true;
}