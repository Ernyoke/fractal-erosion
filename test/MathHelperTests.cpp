#include "MathHelperTests.h"

TEST_F(MathHelperTests, isPowerOf2) {
    ASSERT_TRUE(MathHelper::isPowerOf2(8));
}

TEST_F(MathHelperTests, isNotPowerOf2) {
    ASSERT_FALSE(MathHelper::isPowerOf2(9));
}
