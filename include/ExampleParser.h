/*Author: Sam Matthews (sam.matthews19638@gmail.com)*/

#include "ArgumentParser.h"

#pragma once

class ExampleParser : public ArgumentParser
{
public:
  static void Init();
  /*Properties for each registered argument*/
  inline static std::string inputFile;
  inline static std::string outputFile;
  inline static double multiplier;

protected:
  /*Callback functions*/
  static bool setInputFile(std::string filename);
  static bool setOutputFile(std::string filename);
  static bool setMultiplier(std::string mult);
};