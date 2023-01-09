#include "ui_file.h"
// based on code from Marc's Example (session 5)

UI::UI()
{
#if DEBUG
  std::cout << "Inside UI contructor";
#endif
}

// source code: https://cplusplus.com/forum/general/28440/
std::string UI::toLowerFunction(std::string stringInput)
{
  for (int i=0;i<stringInput.length();i++){ // input.length() gets the length of the string
  // convert every character of input to lowercase ( I think there are other methods to do this)
        stringInput[i]=tolower(stringInput[i]);
      }
  return stringInput;
}


std::string UI::retrieveUserInput(std::string question, std::string selectionOptions[], int numOptions)
{
  // show user the allowed options
  std::cout << question;
  for (int i = 0; i < numOptions - 1; i++)
  {
    std::cout << selectionOptions[i] << ", ";
  }
  // print last option outside forloop to end with an .
  std::cout << selectionOptions[numOptions - 1] << "." << std::endl;
  // retrieve and return choice
  std::string selection = "";
  std::cin >> selection;
  return selection;
}
int UI::retrieveSelection(std::string question, std::string selectionOptions[], int numOptions)
{
  std::string selection = "";
  while (true)
  {
    // let user choose from the allowed options
    selection = retrieveUserInput(question, selectionOptions, numOptions);

    // check if the selection is among the available option
    for (int i = 0; i < numOptions; ++i)
    {
      if (toLowerFunction(selection) == toLowerFunction(selectionOptions[i]))
      {
        return i;
      }
    }
    // if we end up here, this means the selection is not correct,
    // so log a message to user to try again
    std::cout << "\nIncorrect input, please try again\n";
  }          // while
  return -1; // should never be reached
} // retrieveUserSelection()
float UI::retrieveFloatInRange(std::string question, float min, float max)
{
  std::string input;
  float value = 0;
  bool notInRange = true;

  while (notInRange)
  {
    std::cout << question << min << " and " << max
              << std::endl;
    // first capture input in input string
    std::cin >> input;
    // validate if input string can be transformed into a float
    try
    {
      value = std::stof(input);
      // validate range
      if (value >= min && value <= max)
      {
        notInRange = false;
      }
      else
      {
        // value not in range
        std::cout << "Value out of range, please try again." << std::endl;
      }
    }
    catch (const std::exception &e)
    {
      // no float as input
      std::cout << "Invalid input, expecting a number."
                << std::endl;
    }
  }

  return value;
} // while not in range
double UI::retrieveDoubleInRange(std::string question, double min, double max)
{
  std::string input;
  double value = 0;
  bool notInRange = true;

  while (notInRange)
  {
    std::cout << question << min << " and " << max
              << std::endl;
    // first capture input in input string
    std::cin >> input;
    // validate if input string can be transformed into a float
    try
    {
      value = std::stof(input);
      // validate range
      if (value >= min && value <= max)
      {
        notInRange = false;
      }
      else
      {
        // value not in range
        std::cout << "Value out of range, please try again." << std::endl;
      }
    }
    catch (const std::exception &e)
    {
      // no double as input
      std::cout << "Invalid input, expecting a number."
                << std::endl;
    }
  } // while not in range

  return value;
} // retrieveValueInRange()
