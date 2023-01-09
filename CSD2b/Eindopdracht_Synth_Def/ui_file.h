#pragma once
#include <iostream>
#include <cstring>


class UI 
{
  public:
    UI();
    std::string toLowerFunction(std::string stringInput);
    std::string retrieveUserInput(std::string question, std::string selectionOptions[], int numOptions);
    int retrieveSelection(std::string question,std::string selectionOptions[], int numOptions);
    float retrieveFloatInRange(std::string question,float min, float max);
    double retrieveDoubleInRange(std::string question,double min, double max);
};