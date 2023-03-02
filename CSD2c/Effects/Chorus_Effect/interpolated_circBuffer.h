#pragma once
#include "circBuffer.h"
#include "utilities.h"

class Interpolated_CircBuffer : public CircBuffer
{
    Interpolated_CircBuffer();
    ~Interpolated_CircBuffer();
    float output();
};

