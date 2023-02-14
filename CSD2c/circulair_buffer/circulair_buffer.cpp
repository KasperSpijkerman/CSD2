#include "circulair_buffer.h"
#include <iostream>
#include <algorithm>
#include <iterator>

// short 
using namespace std;

CircBuffer::CircBuffer(uint size) : currentSize(size), buffer(new float[currentSize])
{
    cout << "Inside Circbuffer constructor\n";
    wrapValue = 4;
}

CircBuffer::~CircBuffer()
{
    cout << "Inside Circbuffer deconstructor\n";
    deleteBuffer();
    cout << "Buffer is now deleted\n";
}

// writing values according to list with values
void CircBuffer::input(float value)
{  
    buffer[writeHead] = value; 
    cout << buffer[writeHead] << " Is written\n";   
}

// reading values and printing them acooring to readhead
float CircBuffer::output() 
{ 
    cout << buffer[readHead] << " Is being read\n"; 
    if (readHead > 0)
    {
        return buffer[readHead];
    }
    else 
    {
        return 0.0f;
    }
}

// setting a distance between readheader and writeheader
void CircBuffer::setDistance (uint distance) 
{
    currentDistance = distance;
    int readHeadDelayed = readHead - distance;
    if(readHeadDelayed < 0){
        readHead = readHeadDelayed + currentSize;
    } else {
        readHead = readHeadDelayed;
    }
}
// incrementing the writehead 
inline void CircBuffer::incrementWrite()
{
    writeHead++;
}
// incrementing the readhead
inline void CircBuffer::incrementRead()
{
    readHead++;
}
void CircBuffer::incrementHeads() 
{
    incrementRead();
    incrementWrite();
    // wrapping read and writeheads
    wrapHeader(readHead);
    wrapHeader(writeHead);
}
// deleting buffer 
void CircBuffer::deleteBuffer()
{
    delete[] buffer;
}
inline void CircBuffer::wrapHeader(uint& head) 
{
     if (head >= wrapValue)
        {
            head = 0 ;
        }
}
void CircBuffer::setwrapValue(uint value)
{
    wrapValue = value;
}

