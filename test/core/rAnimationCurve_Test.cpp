#include "gtest/gtest.h"
#include "rAnimationCurve.hpp"

struct rTestVector{
	rTestVector(){}
	rTestVector(float xx, float yy, float zz) : x(xx) , y(yy), z (zz) {}
	rTestVector(const rTestVector& v) : x(v.x) , y(v.y), z (v.z) {}

	float x,y,z;
};

typedef rAnimationCurve<rTestVector> rTestVectorCurve;
typedef rTestVectorCurve::KeyType rTestKey;

class Core_rAnimationCurve : public ::testing::Test{
};

void SetupCurve(rTestVectorCurve& curve){
	curve.AddKey(0.0f, rTestVector(0,0,0));
	curve.AddKey(0.1f, rTestVector(10,10,10));
	curve.AddKey(0.2f, rTestVector(20,20,20));
	curve.AddKey(0.3f, rTestVector(30,30,30));
	curve.AddKey(0.4f, rTestVector(40,40,40));
}

TEST(Core_rAnimationCurve, AddKey){
	rTestVector t1(10,10,10);
	rTestVector t2(20,20,20);
	rTestVectorCurve curve;

	size_t count = curve.NumKeys();
	curve.AddKey(0.0f, t1);

	rTestKey* testKey = curve.GetKey(0);
	EXPECT_EQ(testKey->value.x, t1.x);
	EXPECT_EQ(testKey->value.y, t1.y);
	EXPECT_EQ(testKey->value.z, t1.z);

	curve.AddKey(0.0f, t2);
	testKey = curve.GetKey(1);

	EXPECT_EQ(testKey->value.x, t2.x);
	EXPECT_EQ(testKey->value.y, t2.y);
	EXPECT_EQ(testKey->value.z, t2.z);
}

TEST(Core_rAnimationCurve, DetermineKeyframeEmpty){
	rTestVectorCurve curve;

	size_t start, end;
	bool result = curve.DetermineKeyframes(0.0f, start, end);

	EXPECT_FALSE (result);
}

TEST(Core_rAnimationCurve, DetermineKeyframeOneKey){
	rTestVectorCurve curve;
	curve.AddKey(0.0f, rTestVector(0,0,0));

	size_t start, end;
	bool result = curve.DetermineKeyframes(0.0f, start, end);

	EXPECT_TRUE(result);
	EXPECT_EQ(start, 0);
	EXPECT_EQ(end, 0);
}

TEST(Core_rAnimationCurve, DetermineKeyframeT0){
	rTestVectorCurve curve;
	SetupCurve(curve);

	size_t start, end;
	bool result = curve.DetermineKeyframes(0.0f, start, end);

	EXPECT_TRUE(result);
	EXPECT_EQ(start, 0);
	EXPECT_EQ(end, 1);
}

TEST(Core_rAnimationCurve, DetermineKeyframeBetweenFrames){
	rTestVectorCurve curve;
	SetupCurve(curve);

	size_t start, end;
	bool result = curve.DetermineKeyframes(0.25f, start, end);

	EXPECT_TRUE(result);
	EXPECT_EQ(start, 2);
	EXPECT_EQ(end, 3);
}

TEST(Core_rAnimationCurve, DetermineKeyframeBeyondMax){
	rTestVectorCurve curve;
	SetupCurve(curve);

	size_t start, end;
	bool result = curve.DetermineKeyframes(110.0f, start, end);

	EXPECT_TRUE(result);
	EXPECT_EQ(start, curve.NumKeys() - 1);
	EXPECT_EQ(end, curve.NumKeys() - 1);
}

TEST(Core_rAnimationCurve, DetermineKeyframeNegativeTime){
	rTestVectorCurve curve;
	SetupCurve(curve);

	size_t start, end;
	bool result = curve.DetermineKeyframes(-0.5f, start, end);

	EXPECT_TRUE(result);
	EXPECT_EQ(start, 0);
	EXPECT_EQ(end, 0);
}