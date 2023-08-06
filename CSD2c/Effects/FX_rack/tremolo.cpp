#include "tremolo.h"

void Tremolo::prepareToPlay (double sampleRate)
{
   // initializing samplerate
   tremSine.setSamplerate(sampleRate);
   // setting the modulation frequency
   setSpeed(12);
   //set amplitude of modulation depth
   setAmplitude(1);
   // setting dry wet
   setDryWet(1);
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

// TODO create bypass
void Tremolo::bypass (bool bypass) 
{

}
