/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include <sys/stat.h>
#include <iostream>

#include "ExampleParser.h"

/*Standard init function to set default property values and register arguments*/
bool ExampleParser::Initialize()
{
  arguments = {"-o", "-m"};
  functions = {setOutputFile, setMultiplier};
  descriptions = {"Output file", "Multiplier"};
  listArguments = {"", "-c"};
  listFunctions = {setTestValues, setOtherTestValues};
  descriptionPrinter = printCustomHelpMessage; // Set callback to custom printing function
  //allowEmptyArguments = true;
  //allowDuplicateArguments = true;
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

bool ExampleParser::setTestValues(std::vector<std::string> values)
{
  count = values.size();
  return true;
}

bool ExampleParser::setOtherTestValues(std::vector<std::string> values)
{
  other_count = values.size();
  return true;
}

void ExampleParser::printCustomHelpMessage()
{
  std::cout << "This is my custom help message" << std::endl;
}