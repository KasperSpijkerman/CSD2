#include "circulair_buffer.h"

int main()
{
int circBufferSize = 8;
CircBuffer myBuffer(circBufferSize);
float bufferValues[8] = {0.1,0.4,0.2,0.5,0.3,0.6,0.4,0.8};

myBuffer.setwrapValue(8);

// giving bufferValues to input and ouput
for(int i=0; i<circBufferSize; i++)
{ 
    myBuffer.input(bufferValues[i]); 
    myBuffer.output(); 
    myBuffer.incrementHeads(); 
}
return 0; 

}