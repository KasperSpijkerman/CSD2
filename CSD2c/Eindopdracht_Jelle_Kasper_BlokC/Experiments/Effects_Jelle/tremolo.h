//
// Created by Dean on 27/10/2022.
//
#ifndef _TREM_H_
#define _TREM_H_

#pragma once

#include "effect.h"
#include "oscillator.h"
#include "sine.h"
#include "square.h"
#include "saw.h"

class Tremolo : public Effect {

public:
 //constructor and destructor
    Tremolo();
    ~Tremolo();

    //functions
    void prepareToPlay(double sampleRate) override;
    float output(float input) override;

    //setters and getters
    void setAmplitude (float amplitude);
    void setRate (float rate);

protected:
    Oscillator *osc;
    float amp { 1.0f };
};

#endif
