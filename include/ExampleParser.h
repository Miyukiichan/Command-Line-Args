/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include "ArgumentParser.h"

#pragma once

class ExampleParser : public ArgumentParser
{
public:
  static bool Initialize();
  /*Properties for each registered argument*/
  inline static std::string inputFile;
  inline static std::string outputFile;
  inline static double multiplier;
  inline static int count;
  inline static int other_count;

protected:
  /*Callback functions*/
  static bool setInputFile(std::string filename);
  static bool setOutputFile(std::string filename);
  static bool setMultiplier(std::string mult);
  static bool setTestValues(std::vector<std::string> values);
  static bool setOtherTestValues(std::vector<std::string> values);
};