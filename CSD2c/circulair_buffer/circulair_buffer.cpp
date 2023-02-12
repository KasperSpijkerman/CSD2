#include "circulair_buffer.h"
#include <iostream>
#include <algorithm>
#include <iterator>

// short 
using namespace std;

CircBuffer::CircBuffer(uint size) : currentSize(size), buffer(new float[currentSize])
{
    cout << "Inside Circbuffer constructor\n";
    //currentSize = size;
    wrapValue = 8;
    // for (uint i = 0; i < sizeof(buffer); i++){
    //     buffer[i] = 0;
    // }
}

CircBuffer::~CircBuffer()
{
    cout << "Inside Circbuffer deconstructor\n";
    deleteBuffer();
    cout << "Buffer is now deleted\n";
}

void CircBuffer::input(float value)
{  
    buffer[writeHead] = value; 
    cout << buffer[writeHead] << " Is written\n";   
}
float CircBuffer::output() 
{ 
   
    cout << buffer[readHead] << " Is being read\n"; 
    return buffer[readHead];
}
void CircBuffer::setDistance (uint distance) 
{
    currentDistance = distance;
}
inline void CircBuffer::incrementWrite()
{
    wrapHeader(writeHead);
}
inline void CircBuffer::incrementRead()
{
    wrapHeader(readHead);
}
void CircBuffer::incrementHeads() 
{
    // incrementing write and readheads
    incrementRead();
    incrementWrite();
}
void CircBuffer::deleteBuffer()
{
    delete[] buffer;
}
inline void CircBuffer::wrapHeader(uint& head) 
{
     if (head >= wrapValue)
        {
            head = head - wrapValue;
        }
}
void CircBuffer::setwrapValue(uint value)
{
    wrapValue = value;
}

