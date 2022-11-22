//file for main 
#include <iostream>
#include "instrument.h"

int main()
{
    Instrument inst1(220);

    std::cout << "Frequency of the Oscillator object osc is: "
    << inst1.getFreq() << "\n";

    inst1.setFreq(660);

    std::cout << "Frequency has now changed to:  " << inst1.getFreq() << "\n";
    
    

}