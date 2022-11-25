//putting the information in the class
#include <iostream>
#include "instruments.h"

Instruments::Instruments(std::string name,float freq) :
freq(freq), name(name)
{
 std::cout << "Inside Instruments constructor \n";
}

Instruments::~Instruments()
{
  std::cout << "Inside Instruments destructor\n";
}

// void Instruments::playSound()
// {
//   std::cout << name << " is playing sound\n";
// }
// void Instruments::setFreq(float freq)
// {
//   if(freq > 0 && freq < 22000) 
//   {
//     this->freq = freq;
//   } 
//   else {
//     std::cout << "The frequency value is incorrect"
//     << " please present a value in the interval [0, 22000]\n";
//   }
// }
// float Instruments::getFreq()
// {
//     return freq;
// }

// float Instruments::getAmp()
// {
//     return amp;
// }

// void Instruments::setAmp(float amp)
// {
//   if(amp > 0 && amp < 0.9) 
//   {
//     this->amp = amp;
//   } 
//   else {
//     std::cout << "The amplitude value is incorrect"
//     << " please present a value in the interval [0, 0.9]\n";
//   }
// }

