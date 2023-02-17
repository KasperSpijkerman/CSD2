#include <cmath>
#include <iostream>

namespace Util
{
    float mapInRange (float factor, float inLow, float inHigh, float outLow, float outHigh)
    {
        float deltaInOut = (outHigh - outLow) / (inHigh - inLow);
        return outLow + deltaInOut * (factor - inLow);
    }
    float linearMap (float factor, float low, float high) {
        return mapInRange (factor, 0.0, 1.0, low, high);
    }
}