#include "interpolated_circBuffer.h"

float Interpolated_CircBuffer::output()
{
    float low_value = buffer[(int)readHead];
    float high_value = buffer[readBuffer((int)readHead + 1)];
    float factor = readHead - (int)readHead;
    float interpolated_output = Util::linearMap(factor, low_value, high_value);
    return interpolated_output;
}