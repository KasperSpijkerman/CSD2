#include "circBuffer.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>

// short 
using namespace std;

CircBuffer::CircBuffer(uint size) : buffer(new float[size]), currentSize(size),previousReadHead(0.0f)
{
    // setting all values to zero in the buffer.
    memset(buffer, 0, sizeof(float) * currentSize);
}

CircBuffer::~CircBuffer()
{
    deleteBuffer();
}

// writing values according to list with values
void CircBuffer::input(float value)
{  
    buffer[writeHead] = value;   
}


float CircBuffer::cubicInterpolation(float x, float y0, float y1, float y2, float y3)
{
    // cubic interpolation for less noise when changing delaytime
    float a0 = y3 - y2 - y0 + y1;
    float a1 = y0 - y1 - a0;
    float a2 = y2 - y0;
    float a3 = y1;

    return a0 * x * x * x + a1 * x * x + a2 * x + a3;
}


// reading values and outputting them according to readhead
float CircBuffer::output() 
{
    int i = static_cast<int>(readHead);
    float factor = readHead - static_cast<float>(i);

    // Get the surrounding buffer values for cubic interpolation
    int i0 = static_cast<int>((i - 1 + currentSize) % currentSize);
    int i1 = i;
    int i2 = static_cast<int>((i + 1) % currentSize);
    int i3 = static_cast<int>((i + 2) % currentSize);

    float y0 = buffer[i0];
    float y1 = buffer[i1];
    float y2 = buffer[i2];
    float y3 = buffer[i3];

    // Perform cubic interpolation
    float interpolatedSample = cubicInterpolation(factor, y0, y1, y2, y3);

    return interpolatedSample;
}

// setting a distance between readheader and writeheader
void CircBuffer::setDistance (float distance)
{
    this->distance = distance;
    float readHeadBuffer = static_cast<float>(writeHead) - distance;
    if(readHeadBuffer < 0) {
        readHead = readHeadBuffer + static_cast<float>(currentSize);
    }
    else if(readHeadBuffer > static_cast<float>(currentSize))
    {
        readHead = readHeadBuffer - static_cast<float>(currentSize);
    }
    else
    {
        readHead = readHeadBuffer;
    }
}
// incrementing the writehead 
inline void CircBuffer::incrementWrite()
{
    writeHead++;
    wrapwriteHeader(writeHead);
}
// incrementing the readhead
inline void CircBuffer::incrementRead()
{
    readHead++;
    wrapreadHeader(readHead);
}
void CircBuffer::incrementHeads() 
{
    incrementRead();
    incrementWrite();
}
// deleting buffer 
void CircBuffer::deleteBuffer()
{
    delete[] buffer;
}
inline void CircBuffer::wrapreadHeader(float& head)
{
     if (head >= currentSize)
        {
            head = 0 ;
        }
}

inline void CircBuffer::wrapwriteHeader(uint& head)
{
    if (head >= currentSize)
    {
        head = 0 ;
    }
}

