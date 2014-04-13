#include "gtest/gtest.h"
#include "rAnimationTrack.hpp"

class rTestAnimationTrack : public rAnimationTrack{
public:
	rTestAnimationTrack(unsigned short handle) : rAnimationTrack(handle){}
	rVector3 TestInterpolateVector3(const rVector3AnimationCurve& curve, float animationTime) const { return InterpolateVector3(curve, animationTime); }
	rQuaternion TestInterpolateQuaternion(const rQuaternionAnimationCurve& curve, float animationTime) const { return InterpolateQuaternion(curve, animationTime); }
};

class Core_rAnimationTrack : public ::testing::Test{
};

void SetupVectorKeys(rVector3AnimationCurve& curve){
	curve.AddKey(0.0f, rVector3(0,0,0));
	curve.AddKey(0.1f, rVector3(10,10,10));
	curve.AddKey(0.2f, rVector3(20,20,20));
	curve.AddKey(0.3f, rVector3(30,30,30));
	curve.AddKey(0.4f, rVector3(40,40,40));
}

void SetupQuaternionKeys(rQuaternionAnimationCurve& curve){
	curve.AddKey(0.0f, rQuaternion(0,0,0));
	curve.AddKey(0.1f, rQuaternion(0,90,0));
	curve.AddKey(0.2f, rQuaternion(0,180,0));
	curve.AddKey(0.3f, rQuaternion(0,270,0));
}

TEST(Core_rAnimationTrack, InterpolateQuaternion){
	rTestAnimationTrack animTrack(0);
	rQuaternionAnimationCurve& rotationCurve = animTrack.RotationCurve();
	SetupQuaternionKeys(rotationCurve);
	
	rQuaternion test(0,0,0);
	rQuaternion interpolate = animTrack.TestInterpolateQuaternion(rotationCurve, 0.0f);
	
	EXPECT_FLOAT_EQ(interpolate.x , test.x);
	EXPECT_FLOAT_EQ(interpolate.y , test.y);
	EXPECT_FLOAT_EQ(interpolate.z , test.z);
	EXPECT_FLOAT_EQ(interpolate.w , test.w);
	
	test.SetFromEulerAngles(0,45,0);
	interpolate = animTrack.TestInterpolateQuaternion(rotationCurve, 0.05f);
	
	EXPECT_FLOAT_EQ(interpolate.x , test.x);
	EXPECT_FLOAT_EQ(interpolate.y , test.y);
	EXPECT_FLOAT_EQ(interpolate.z , test.z);
	EXPECT_FLOAT_EQ(interpolate.w , test.w);
	
	test.SetFromEulerAngles(0,180,0);
	interpolate = animTrack.TestInterpolateQuaternion(rotationCurve, 0.2f);
	
	EXPECT_FLOAT_EQ(interpolate.x , test.x);
	EXPECT_FLOAT_EQ(interpolate.y , test.y);
	EXPECT_FLOAT_EQ(interpolate.z , test.z);
	EXPECT_FLOAT_EQ(interpolate.w , test.w);
	
	test.SetFromEulerAngles(0,270,0);
	interpolate = animTrack.TestInterpolateQuaternion(rotationCurve, 0.3f);
	
	EXPECT_FLOAT_EQ(interpolate.x , test.x);
	EXPECT_FLOAT_EQ(interpolate.y , test.y);
	EXPECT_FLOAT_EQ(interpolate.z , test.z);
	EXPECT_FLOAT_EQ(interpolate.w , test.w);
}

TEST(Core_rAnimationTrack, InterpolateVector3){
	rTestAnimationTrack animTrack(0);
	rVector3AnimationCurve& translationCurve = animTrack.TranslationCurve();
	SetupVectorKeys(translationCurve);
	
	rVector3 interpolate = animTrack.TestInterpolateVector3(translationCurve, 0.0f);
	
	EXPECT_FLOAT_EQ(interpolate.x , 0.0f);
	EXPECT_FLOAT_EQ(interpolate.y , 0.0f);
	EXPECT_FLOAT_EQ(interpolate.z , 0.0f);
	
	interpolate = animTrack.TestInterpolateVector3(translationCurve, 0.15f);
	
	EXPECT_FLOAT_EQ(interpolate.x , 15.0f);
	EXPECT_FLOAT_EQ(interpolate.y , 15.0f);
	EXPECT_FLOAT_EQ(interpolate.z , 15.0f);
	
	interpolate = animTrack.TestInterpolateVector3(translationCurve, 0.27f);
	
	EXPECT_FLOAT_EQ(interpolate.x , 27.0f);
	EXPECT_FLOAT_EQ(interpolate.y , 27.0f);
	EXPECT_FLOAT_EQ(interpolate.z , 27.0f);
	
	interpolate = animTrack.TestInterpolateVector3(translationCurve, 0.4f);
	
	EXPECT_FLOAT_EQ(interpolate.x , 40.0f);
	EXPECT_FLOAT_EQ(interpolate.y , 40.0f);
	EXPECT_FLOAT_EQ(interpolate.z , 40.0f);
	
	interpolate = animTrack.TestInterpolateVector3(translationCurve, 0.7f);
	
	EXPECT_FLOAT_EQ(interpolate.x , 40.0f);
	EXPECT_FLOAT_EQ(interpolate.y , 40.0f);
	EXPECT_FLOAT_EQ(interpolate.z , 40.0f);
}

