#include "MathHelperTests.h"

constexpr float abs_error = 0.01f;

TEST_F(MathHelperTests, isPowerOf2) {
    ASSERT_TRUE(MathHelper::isPowerOf2(8));
}

TEST_F(MathHelperTests, isNotPowerOf2) {
    ASSERT_FALSE(MathHelper::isPowerOf2(9));
}

TEST_F(MathHelperTests, normalize_between_0_and_1) {
    float normalized = MathHelper::normalize(15.0f, 0.0f, 30.0f);
    ASSERT_NEAR(normalized, 0.5f, abs_error);
}

TEST_F(MathHelperTests, clampBetween_return_value) {
    float value = 1.0f;
    float min = 0.0f;
    float max = 2.0f;
    ASSERT_NEAR(MathHelper::clampBetween(value, min, max), value, abs_error);
}

TEST_F(MathHelperTests, clampBetween_clamp_min) {
    float value = -1.0f;
    float min = 0.0f;
    float max = 2.0f;
    ASSERT_NEAR(MathHelper::clampBetween(value, min, max), min, abs_error);
}

TEST_F(MathHelperTests, clampBetween_clamp_max) {
    float value = 3.0f;
    float min = 0.0f;
    float max = 2.0f;
    ASSERT_NEAR(MathHelper::clampBetween(value, min, max), max, abs_error);
}
