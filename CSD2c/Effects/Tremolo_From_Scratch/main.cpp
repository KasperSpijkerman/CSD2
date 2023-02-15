#include "tremolo.h"

int main()
{
    Tremolo trem;
    trem.prepareToPlay(44100);
    trem.setAmplitude(0.5);
    trem.setSpeed(4);
    return 0;
}