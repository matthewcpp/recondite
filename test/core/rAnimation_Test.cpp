#include "gtest/gtest.h"
#include "rAnimationPlayer.hpp"

class rTestAnimationTrack : public rAnimationTrack{
public:
	rTestAnimationTrack();
	void DetermineKeyframesTest(float animationTime, unsigned short keyframeHint, unsigned short& start, unsigned short& end) const;
};

rTestAnimationTrack::rTestAnimationTrack() : rAnimationTrack(0){}
void rTestAnimationTrack::DetermineKeyframesTest(float animationTime, unsigned short keyframeHint, unsigned short& start, unsigned short& end) const{
	DetermineKeyframes(animationTime, keyframeHint, start, end);
}

class Core_rAnimationTrack : public ::testing::Test{
protected:
	static unsigned short keyframeHint;
	static unsigned short start;
	static unsigned short end;
	static rTestAnimationTrack* animationTrack;

	virtual void SetUp(){
		start = 999;
		end = 999;

		animationTrack = new rTestAnimationTrack();
		animationTrack->PushKeyframe(0.0f, rVector3(0,0,0), rQuaternion(0,0,0), rVector3::OneVector);
		animationTrack->PushKeyframe(0.1f, rVector3(0,0,0), rQuaternion(0,45,0), rVector3::OneVector);
		animationTrack->PushKeyframe(0.2f, rVector3(0,0,0), rQuaternion(0,90,0), rVector3::OneVector);
		animationTrack->PushKeyframe(0.3f, rVector3(0,0,0), rQuaternion(0,135,0), rVector3::OneVector);
		animationTrack->PushKeyframe(0.4f, rVector3(0,0,0), rQuaternion(0,180,0), rVector3::OneVector);
	}

	virtual void TearDown(){
		delete animationTrack;
	}
};

unsigned short Core_rAnimationTrack::start = 999;
unsigned short Core_rAnimationTrack::end = 999;
rTestAnimationTrack* Core_rAnimationTrack::animationTrack = NULL;

TEST_F(Core_rAnimationTrack, DetermineKeyframeTime0){
	animationTrack->DetermineKeyframesTest(0.0f, 0, start, end);

	ASSERT_EQ(start, 0);
	ASSERT_EQ(end, 1);
}

TEST_F(Core_rAnimationTrack, DetermineKeyframeBetween0and1){
	animationTrack->DetermineKeyframesTest(0.05f, 0, start, end);

	ASSERT_EQ(start, 0);
	ASSERT_EQ(end, 1);
}

TEST_F(Core_rAnimationTrack, DetermineKeyframeTime1){
	animationTrack->DetermineKeyframesTest(0.1f, 0, start, end);

	ASSERT_EQ(start, 1);
	ASSERT_EQ(end, 2);
}

TEST_F(Core_rAnimationTrack, DetermineKeyframeTimeMax){
	animationTrack->DetermineKeyframesTest(0.4f, 0, start, end);

	ASSERT_EQ(start, 4);
	ASSERT_EQ(end, 4);
}

TEST_F(Core_rAnimationTrack, DetermineKeyframeTimePastMax){
	animationTrack->DetermineKeyframesTest(0.4f, 0, start, end);

	ASSERT_EQ(start, 4);
	ASSERT_EQ(end, 4);
}

TEST_F(Core_rAnimationTrack, GetKeyframe){
	rAnimationKeyframe* keyframe = animationTrack->GetKeyframe(2);

	ASSERT_FALSE(keyframe == NULL);
	ASSERT_FLOAT_EQ(keyframe->time, 0.2f);
}

TEST_F(Core_rAnimationTrack, GetKeyframeOutOfRange){
	rAnimationKeyframe* keyframe = animationTrack->GetKeyframe(25);

	ASSERT_TRUE(keyframe == NULL);
}

TEST_F(Core_rAnimationTrack, PushKeyFrame){
	size_t keyCount = animationTrack->NumKeyframes();

	float keyTime = 1.0f;
	rVector3 translate(0.0f, 0.0f, 0.0f);
	rQuaternion rotate(0.0f, 80.0f, 0.0f);
	rVector3 scale(1.0f, 1.0f, 1.0f);

	animationTrack->PushKeyframe(keyTime, translate, rotate, scale);

	ASSERT_EQ(keyCount + 1, animationTrack->NumKeyframes());

	rAnimationKeyframe* keyframe = animationTrack->GetKeyframe( animationTrack->NumKeyframes() - 1);

	ASSERT_FALSE(keyframe == NULL);
	ASSERT_FLOAT_EQ(keyframe->time, keyTime);
	ASSERT_EQ(keyframe->translation, translate);
	ASSERT_EQ(keyframe->rotation, rotate);
	ASSERT_EQ(keyframe->scale, scale);
}

TEST_F(Core_rAnimationTrack, Clear){
	ASSERT_NE(animationTrack->NumKeyframes(), 0);
	animationTrack->Clear();
	ASSERT_EQ(animationTrack->NumKeyframes(), 0);
}