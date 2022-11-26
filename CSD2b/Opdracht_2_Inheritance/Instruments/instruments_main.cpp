//file for main 
#include <iostream>
#include "bass.h"
#include "guitar.h"

int main()
{
    Bass FenderBass("Fender Jazz",200,0);
    Guitar GibsonGuitar("Gibson Les Paul",400,0);
    FenderBass.slide();
    GibsonGuitar.screech();
    FenderBass.setAmp(0.9);
    GibsonGuitar.setAmp(0.8);
    FenderBass.setFreq(50);
    GibsonGuitar.setFreq(2000);
    std::cout << "The Bass got louder, amp: " << FenderBass.getAmp() << "\n";
    std::cout << "The Bass got loooow, freq:  " << FenderBass.getFreq() << "\n";
    std::cout << "The Guitar got louder, amp: " << GibsonGuitar.getAmp() << "\n";
    std::cout << "The Guitar got Hiiiigh, freq: " << GibsonGuitar.getFreq() << "\n";

    
return 0;
}