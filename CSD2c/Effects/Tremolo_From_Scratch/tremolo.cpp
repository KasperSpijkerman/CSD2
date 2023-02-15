#include "tremolo.h"

void Tremolo::prepareToPlay (double sampleRate)
{
   std::cout << "Samplerate is set to: " << sampleRate << "\n";
   // initializing samplerate
   tremSine.setSamplerate(sampleRate);
   tremSine.setFrequency(4);
}


float Tremolo::output (float input) 
{
   float tremSignal = tremSine.tick();
   tremSignal *= amp;
   tremSignal += 1.0f - amp;
   return input * tremSignal;
}

void Tremolo::setAmplitude(float amplitude)
{
   amp = amplitude;
   std::cout << "Amp is set to: " << amp << "\n";
}
    
void Tremolo::setSpeed(float speed)
{
   tremSine.setFrequency(speed);
   std::cout << "Speed is set to: " << speed << " Hz\n";
}

