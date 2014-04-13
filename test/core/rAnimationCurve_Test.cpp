#include "gtest/gtest.h"

#include "rVector3.hpp"
#include "rAnimationCurve.hpp"

typedef rAnimationCurve<rVector3> rTestVectorCurve;
typedef rTestVectorCurve::KeyType rTestKey;

class Core_rAnimationCurve : public ::testing::Test{
};

void SetupCurve(rTestVectorCurve& curve){
	curve.AddKey(0.0f, rVector3(0,0,0));
	curve.AddKey(0.1f, rVector3(10,10,10));
	curve.AddKey(0.2f, rVector3(20,20,20));
	curve.AddKey(0.3f, rVector3(30,30,30));
	curve.AddKey(0.4f, rVector3(40,40,40));
}

TEST(Core_rAnimationCurve, AddKey){
	rVector3 t1(10,10,10);
	rVector3 t2(20,20,20);
	rTestVectorCurve curve;

	size_t count = curve.NumKeys();
	curve.AddKey(0.0f, t1);

	const rTestKey* testKey = curve.GetKey(0);
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
	curve.AddKey(0.0f, rVector3(0,0,0));

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

TEST(Core_rAnimationCurve, AllocateFrames){
	rTestVectorCurve curve;

	for (size_t i = 0; i < 4; i++){
		curve.AddKey(float(i), rVector3(i,i,i));
	}

	EXPECT_EQ (curve.NumKeys(), 4);

	curve.AllocateFrames(2);

	EXPECT_EQ(curve.NumKeys(), 2);
}

TEST(Core_rAnimationCurve, SetKey){
	rTestVectorCurve curve;

	curve.AllocateFrames(2);
	rVector3 t1(1.0f, 2.0f, 3.0f);

	EXPECT_TRUE(curve.SetKey(0, 1.0, t1));
	const rTestVectorCurve::KeyType* key = curve.GetKey(0);

	EXPECT_EQ(key->time, 1.0f);
	EXPECT_EQ(key->value.x, t1.x);
	EXPECT_EQ(key->value.y, t1.y);
	EXPECT_EQ(key->value.z, t1.z);
}