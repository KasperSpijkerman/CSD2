#pragma once
#include <iostream>


class UI 
{
  public:
    UI();
    std::string retrieveUserInput(std::string selectionOptions[], int numOptions);
    int retrieveUserSelection(std::string selectionOptions[], int numOptions);
    float retrieveRootnoteInRange(float min, float max);
    double retrieveBPMInRange(double min, double max);
    double retrieveModulationInRange(double min, double max);


};