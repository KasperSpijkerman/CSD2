//
// Created by Dean on 15/02/2023.
//

#include "waveshaper.h"

WaveShaper::WaveShaper (){
    
}

WaveShaper::~WaveShaper() {
    delete[] buffer;
}

float WaveShaper::output (float input) {  //map the input to values in the transfer curve
    // Push the index from -1 - 1 to 0 - 2. Then multiply by half the bufferSize to find its nearest position
    float index = (input + 1.0f) * (bufferSize * 0.5f);
    // truncate index (remove everything after the decimal point)
    int i = (int) trunc (index);
    // subtract from the original value to find the remainder
    float indexDecimal = index - (float) i;

    // the remainder is the interpolation factor. To accurately estimate the value between two buffer positions  
    return (linearMap(indexDecimal, buffer[i], buffer[i + 1])*wet) + (input*dry);
}

void WaveShaper::setDrive (float k) { 
    // fill buffer using arc-tan function
    for (int i = 0; i < bufferSize; ++i) {
        float x = mapInRange (i, 0.0f, bufferSize, -1.0f, 1.0f);
        buffer[i] = atan (k * x) / atan (k);
    }
}

void WaveShaper::prepareToPlay(double sampleRate){
    bufferSize = 1024;
    buffer = new float[bufferSize];
    setDrive(2.0f);
}