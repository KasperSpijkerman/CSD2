#pragma once
#include "circBuffer.h"
#include "utilities.h"

class Interpolated_CircBuffer : public CircBuffer
{
    using uint = unsigned int;
public:

    Interpolated_CircBuffer(uint size);
    ~Interpolated_CircBuffer();
    // returning interpolated buffer
    float output();

};

