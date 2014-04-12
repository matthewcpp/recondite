#ifndef R_ANIMATION_HPP
#define R_ANIMATION_HPP

#include <vector>
#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rVector3.hpp"
#include "rQuaternion.hpp"
#include "rMatrix4.hpp"


#include "rAnimationTrack.hpp"

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
