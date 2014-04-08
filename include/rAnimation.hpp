#ifndef R_ANIMATION_HPP
#define R_ANIMATION_HPP

#include <vector>
#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rVector3.hpp"
#include "rQuaternion.hpp"
#include "rMatrix4.hpp"

#include "rMatrixUtil.hpp"

struct rAnimationKeyframe {
	rAnimationKeyframe() : time(0.0f), translation(rVector3::ZeroVector), rotation(rQuaternion::Identity), scale(rVector3::OneVector){}
	rAnimationKeyframe(float t, const rVector3& trans, const rQuaternion& rot, const rVector3& s)
	: time(t), translation(trans), rotation(rot), scale(s){}
	
	void Set(float t, const rVector3& trans, const rQuaternion& rot, const rVector3& s);
	
	float time;
	rVector3 translation;
	rQuaternion rotation;
	rVector3 scale;
};

typedef std::vector<rAnimationKeyframe> rKeyframeVector;

class rAnimationTrack{
public:
	rAnimationTrack(unsigned short handle);
	
public:
	unsigned short Handle() const;
	void Clear();
	
	size_t NumKeyframes() const;
	const rKeyframeVector& Keyframes() const;
	
	void AllocateFrames(size_t count);
	void SetKeyframe(size_t i, float time, const rVector3& translation, rQuaternion& rotation, const rVector3& scale);
	size_t PushKeyframe(float time, const rVector3& translation, rQuaternion& rotation, const rVector3& scale);
	rAnimationKeyframe* GetKeyframe(size_t index);

	unsigned short InterpolateKeyframe(float animationTime, rMatrix4& transform, unsigned short keyframeHint) const;
	
protected:
	void DetermineKeyframes(float animationTime, unsigned short keyframeHint, unsigned short& start, unsigned short& end) const;

private:
	unsigned short m_handle;
	rKeyframeVector m_keyframes;
};

typedef std::map<unsigned short, rAnimationTrack*> rAnimationTrackMap;

class rAnimation{
public:
	rAnimation(const rString& name);
	rAnimation(const rString& name, float duration);
	~rAnimation();
	
public:
	void Clear();
	rString Name() const;
	
	rAnimationTrack* GetTrack(unsigned short handle) const;
	rAnimationTrack* CreateTrack(unsigned short handle);
	void DeleteTrack(unsigned short handle);
	size_t NumTracks() const;

	float Duration() const;
	void SetDuration(float duration);
	
private:
	rString m_name;
	float m_duration;
	
	rAnimationTrackMap m_tracks;
};

typedef std::map<rString, rAnimation*> rAnimationMap;

#endif
