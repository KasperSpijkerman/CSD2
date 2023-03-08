#include "amplifier.h"



void Amplifier::prepareToPlay (double sampleRate)
{
   std::cout << "Samplerate is set to: " << sampleRate << "\n";
}


float Amplifier::output (float input) 
{
   std::cout << "Input is: " << input << "\n";
   int output = input*10;
   std::cout << "Ouput is: " << output << "\n";

   return output;
   
}