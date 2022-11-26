//putting the information in the class
#include <iostream>
#include "bass.h"

Bass::Bass(std::string name, float freq,float amp) : Instruments(name,freq,amp)
{
std::cout << "Constructor from the: " << name <<"\n" << "Main Frequency bass is: " << freq << "\n" << "Default amp bass is: " << amp << "\n";
}


Bass::~Bass()
{
std::cout << "Destructor from the: " << name <<"\n";
}



void Bass::slide()
{
  std::cout << name << " Does voooom!\n ";
}


