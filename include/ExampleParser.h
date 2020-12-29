/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include "ArgumentParser.h"

#pragma once

class ExampleParser : public ArgumentParser
{
public:
  static bool Initialize();
  /*Properties for each registered argument*/
  inline static std::string inputFile = "";
  inline static std::string outputFile = "output.txt";
  inline static double multiplier = 1;
  inline static int count = 0;
  inline static int other_count = 0;

protected:
  static void printHelpMessage();

private:
  /*Callback functions*/
  static bool setInputFile(std::string filename);
  static bool setOutputFile(std::string filename);
  static bool setMultiplier(std::string mult);
  static bool setTestValues(std::vector<std::string> values);
  static bool setOtherTestValues(std::vector<std::string> values);
};