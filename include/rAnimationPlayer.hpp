#ifndef R_ANIMATIONPLAYER_HPP
#define R_ANIMATIONPLAYER_HPP

#include <vector>

#include "rTypes.hpp"
#include "rMatrix4.hpp"

#include "rSkeleton.hpp"

#include "rTime.hpp"

typedef std::vector<rMatrix4> rMatrix4Vector;

class rAnimationPlayer{
public:
	rAnimationPlayer();

public:
	bool PlayAnimation(const rString& name);
	bool SetAnimation(const rString& name);

	void Pause();
	void Play();
	void Stop();

	void SetSkeleton(rSkeleton* skeleton);

	void UpdateTransformData();

	void Update(const rTime& time);

	const rMatrix4Vector& GetTransformData() const;
	float AnimationTime() const;

	const rAnimation* CurrentAnimation() const;
private:
	void UpdateTransformDataRec(rBone* parentBone, rBone* currentBone);

private:
	float m_animationTime;
	rSkeleton* m_skeleton;
	rAnimation* m_currentAnimation;

	rMatrix4Vector m_transformData;
	rUnsignedShortArray m_keyframeInfo;

	bool m_isLooping;
	bool m_playing;
};

#endif
