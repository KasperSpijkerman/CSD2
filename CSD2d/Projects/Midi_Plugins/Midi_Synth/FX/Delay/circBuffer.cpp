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




// reading values and outputting them according to readhead
float CircBuffer::output() 
{
    int index0 = static_cast<int>(readHead);
    int index1 = (index0 + 1) % currentSize;
    float fraction = readHead - static_cast<float>(index0);

    // Perform linear interpolation between adjacent samples
    float interpolatedSample = util.linearMap(fraction, buffer[index0], buffer[index1]);
    return interpolatedSample;

}

// setting a distance between readheader and writeheader
void CircBuffer::setDistance (float distance)
{
    this->distance = distance;
    float readHeadBuffer = writeHead - distance;
    if(readHeadBuffer < 0) {
        readHead = readHeadBuffer + currentSize;
    }
    else if(readHeadBuffer > currentSize)
    {
        readHead = readHeadBuffer - currentSize;
    }
     else {
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

