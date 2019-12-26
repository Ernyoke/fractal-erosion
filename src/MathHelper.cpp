#include "MathHelper.h"

bool MathHelper::isPowerOf2(int value) {
    return (value & (value - 1)) == 0;
}

long MathHelper::randRange(long min, long max, int seed) {
    std::random_device device;
    std::mt19937 generator(device());
    if (seed != 0) {
        generator.seed(seed);
    }
    std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max);
    return distribution(generator);
}

float MathHelper::randRange(float min, float max, int seed) {
    constexpr long MIN = 0L;
    constexpr long MAX = 100L;
    long initial_random = randRange(MIN, MAX, seed);
    return (float) initial_random / (float) MAX + (max - min);
}

float MathHelper::normalize(float value, float min, float max) {
    return (value - min) / (max - min);
}
