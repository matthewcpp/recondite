#include "gtest/gtest.h"
#include "rTypes.hpp"
#include "rString.hpp"

class Core_rArrayString : public ::testing::Test{
};

TEST(Core_rArrayString, Size){
	rArrayString arr;
	ASSERT_EQ(arr.size(), 0);

	arr.push_back("test0");
	ASSERT_EQ(arr.size(), 1);
}

TEST(Core_rArrayString, GetByIndex){
	rArrayString arr;
	arr.push_back("test0");
	arr.push_back("test1");
	arr.push_back("test2");

	ASSERT_EQ (arr[0], "test0");
	ASSERT_EQ (arr[1], "test1");
	ASSERT_EQ (arr[2], "test2");
}

TEST(Core_rArrayString, PushBack){
	rArrayString arr;

	arr.push_back("test0");
	ASSERT_EQ (arr[0], "test0");

	arr.push_back("test1");
	ASSERT_EQ (arr[1], "test1");
}


TEST(Core_rArrayString, Clear){
	rArrayString arr;
	arr.push_back("test0");
	arr.push_back("test1");
	arr.push_back("test2");

	ASSERT_EQ(arr.size(), 3);

	arr.clear();

	ASSERT_EQ(arr.size(), 0);
}