#include "effect.h"

#pragma once

class CircBuffer {
    using uint = unsigned int;

public:
    CircBuffer(uint size);
    ~CircBuffer(); 
    
    // input/output and incrementing the heads
    void input (float value); 
    float output(); 
    void incrementHeads(); 

    // setters
    void setDistance (uint distance);
    void setSize(uint size);

    
private:
    inline void wrapHeader (uint& head);
    inline void incrementWrite();
    inline void incrementRead(); 
    void deleteBuffer();

    float* buffer;
    uint currentSize { 0 };
    uint distance { 0 };
    uint writeHead { 0 }, readHead { 0 };
};