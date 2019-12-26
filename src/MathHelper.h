#ifndef FRACTALS_MATHHELPER_H
#define FRACTALS_MATHHELPER_H

#include <random>

namespace MathHelper {
    // Returns true if the in the input value is the power of 2.
    bool isPowerOf2(int value);

    long randRange(long min, long max, int seed);

    float randRange(float min, float max, int seed);

    float normalize(float value, float min, float max);
};


#endif //FRACTALS_MATHHELPER_H
