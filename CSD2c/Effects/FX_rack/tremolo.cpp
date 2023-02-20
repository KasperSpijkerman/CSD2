#include "tremolo.h"

void Tremolo::prepareToPlay (double sampleRate)
{
   std::cout << "Samplerate is set to: " << sampleRate << "\n";
   // initializing samplerate
   tremSine.setSamplerate(sampleRate);
   // setting the modulation frequency
   setSpeed(8);
   // setting dry wet;
   setDryWet(0.5);
}


float Tremolo::output (float input) 
{
   auto tremSignal = tremSine.getSample();
   tremSine.tick();
   //std::cout << tremSignal << "\n";
   tremSignal *= amp;
   tremSignal += 1.0f - amp;
   // returning modulated or dry signal based on dry wet
   return (input * tremSignal* wet) + (input * dry);
}

void Tremolo::setAmplitude(float amplitude)
{
   amp = amplitude;
}
    
void Tremolo::setSpeed(float speed)
{
   tremSine.setFrequency(speed);
}


void Tremolo::bypass (bool bypass) 
{

}
