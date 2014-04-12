#include "gtest/gtest.h"
#include "rMathUtil.hpp"

class Math_rMathUtil : public ::testing::Test{
};

TEST(Math_rMathUtil, ConvertRange){
	EXPECT_FLOAT_EQ(50.0f, rMath::ConvertRange(0.5f, 0.0f, 1.0f, 0.0f, 100.0f));
	EXPECT_FLOAT_EQ(0.25f, rMath::ConvertRange(25.0f, 0.0f, 100.0f, 0.0f, 1.0f));

	EXPECT_FLOAT_EQ(-50.0f, rMath::ConvertRange(-0.5f, -1.0f, 0.0f, -100.0f, 0.0f));
	EXPECT_FLOAT_EQ(-0.25f, rMath::ConvertRange(-25.0f, -100.0f, 0.0f, -1.0f, 0.0f));
}