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

TEST(Math_rMathUtil, Max3){
	float a = 0.9f;
	float b = 1.0f;
	float c = 1.1f;

	EXPECT_EQ(rMath::Max3(a,b,c), c);

	float d = -0.9f;
	float e = -1.0f;
	float f = -1.1f;

	EXPECT_EQ(rMath::Max3(d,e,f), d);
}