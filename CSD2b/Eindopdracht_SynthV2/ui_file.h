#pragma once
#include <iostream>


class UI 
{
  public:
    UI();
    std::string retrieveUserInput(std::string selectionOptions[], int numOptions);
    int retrieveScaleSelection(std::string selectionOptions[], int numOptions);
    int retrieveSynthSelection(std::string selectionOptions[], int numOptions);
    int retrieveKeySelection(std::string selectionOptions[], int numOptions);
    float retrieveOctaveInRange(float min, float max);
    double retrieveBPMInRange(double min, double max);
    double retrieveModulationInRange(double min, double max);


};