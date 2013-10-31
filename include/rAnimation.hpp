#ifndef R_ANIMATION_HPP
#define R_ANIMATION_HPP

#include <vector>
#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rVector3.hpp"
#include "rQuaternion.hpp"

struct rAnimationKeyframe {
	rAnimationKeyframe(){}
	rAnimationKeyframe(float t, const rVector3& trans, const rQuaternion& rot, const rVector3& s)
	: time(t), translation(trans), rotation(rot), scale(s){}
	
	void Set(float t, const rVector3& trans, const rQuaternion& rot, const rVector3& s);
	
	float time;
	rVector3 translation;
	rVector3 scale;
	rQuaternion rotation;
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
	void PushKeyframe(float time, const rVector3& translation, rQuaternion& rotation, const rVector3& scale);
	
private:
	unsigned short m_handle;
	rKeyframeVector m_keyframes;
};

typedef std::map<unsigned short, rAnimationTrack*> rAnimationTrackMap;

class rAnimation{
public:
	rAnimation(const rString& name);
	~rAnimation();
	
public:
	void Clear();
	rString Name() const;
	
	const rAnimationTrack* GetTrack(unsigned short handle) const;
	rAnimationTrack* CreateTrack(unsigned short handle);
	void DeleteTrack(unsigned short handle);
	size_t NumTracks() const;
	
private:
	rString m_name;
	
	rAnimationTrackMap m_tracks;
};

typedef std::map<rString, rAnimation*> rAnimationMap;

#endif
