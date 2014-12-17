#include "gtest/gtest.h"

#include "rColor.hpp"


class Core_rColor : public ::testing::Test{
};

TEST(Core_rColor, Comparator){
	rColorComparator comparator;

	rColor c1(10, 100, 200, 255);
	rColor c2(23, 101, 202, 255);
	EXPECT_TRUE(comparator(c1, c2));

	c1.Set(10, 100, 200, 255);
	c2.Set(10, 101, 202, 255);
	EXPECT_TRUE(comparator(c1, c2));

	c1.Set(10, 101, 200, 255);
	c2.Set(10, 101, 202, 255);
	EXPECT_TRUE(comparator(c1, c2));

	c1.Set(10, 101, 202, 101);
	c2.Set(10, 101, 202, 255);
	EXPECT_TRUE(comparator(c1, c2));

	c1.Set(100, 200, 202, 101);
	c2.Set(100, 101, 202, 255);
	EXPECT_FALSE(comparator(c1, c2));

	c1.Set(10, 101, 251, 101);
	c2.Set(10, 101, 202, 255);
	EXPECT_FALSE(comparator(c1, c2));

	c1.Set(10, 101, 202, 255);
	c2.Set(10, 101, 202, 0);
	EXPECT_FALSE(comparator(c1, c2));

	c1 = c2;
	EXPECT_FALSE(comparator(c1, c2));
}