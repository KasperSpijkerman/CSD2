

#include "AdsrData.h"


void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    // setting the parameters
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    // setting the ADSR params
    setParameters(adsrParams);
}