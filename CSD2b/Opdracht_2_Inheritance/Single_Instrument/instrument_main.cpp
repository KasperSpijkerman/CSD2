//file for main 
#include <iostream>
#include "instrument.h"

int main()
{
    Instrument inst1(220,0);

    std::cout << "Frequency of the Oscillator: " << inst1.getFreq() << "\n";
    std::cout << "Amplitude of The Oscillator " << inst1.getAmp() << "\n";
    inst1.setFreq(660);
    inst1.setAmp(0.5);
    std::cout << "Frequency has now changed to:  " << inst1.getFreq() << "\n";
    std::cout << "Amplitude has now changed to:   " << inst1.getAmp() << "\n";
    
    

}