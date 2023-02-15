#include "amplifier.h"

int main()
{
    Amplifier amp;
    amp.prepareToPlay(44100);
    amp.output(10);
    
    return 0;
}