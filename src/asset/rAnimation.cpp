#include "rAnimation.hpp"

void rAnimationKeyframe::Set(float t, const rVector3& trans, const rQuaternion& rot, const rVector3& s){
	time = t;
	translation = trans;
	rotation = rot;
	scale = s;
}

rAnimationTrack::rAnimationTrack(unsigned short handle){
	m_handle = handle;
}

unsigned short rAnimationTrack::Handle() const{
	return m_handle;
}

void rAnimationTrack::Clear(){
	m_keyframes.clear();
}

size_t rAnimationTrack::NumKeyframes() const{
	return m_keyframes.size();
}

const rKeyframeVector& rAnimationTrack::Keyframes() const{
	return m_keyframes;
}

void rAnimationTrack::AllocateFrames(size_t count){
	m_keyframes.resize(count);
}

void rAnimationTrack::SetKeyframe(size_t i, float time, const rVector3& translation, rQuaternion& rotation, const rVector3& scale){
	if (i < m_keyframes.size()){
		m_keyframes[i].Set(time, translation, rotation, scale);
	}
}

void rAnimationTrack::PushKeyframe(float time, const rVector3& translation, rQuaternion& rotation, const rVector3& scale){
	rAnimationKeyframe keyframe(time, translation, rotation, scale);
	m_keyframes.push_back(keyframe);
}

rAnimation::rAnimation(const rString& name){
	m_name = name;
}

rAnimation::~rAnimation(){
	Clear();
}

void rAnimation::Clear(){
	for (rAnimationTrackMap::iterator it = m_tracks.begin(); it != m_tracks.end(); ++it)
		delete it->second;
	
	m_tracks.clear();
}

rString rAnimation::Name() const{
	return m_name;
}

const rAnimationTrack* rAnimation::GetTrack(unsigned short handle) const{
	rAnimationTrackMap::const_iterator result = m_tracks.find(handle);
	
	if (result == m_tracks.end()){
		return NULL;
	}
	else{
		return result->second;
	}
}

rAnimationTrack* rAnimation::CreateTrack(unsigned short handle){
	if (m_tracks.count(handle)){
		return NULL;
	}
	else{
		rAnimationTrack* animationTrack = new rAnimationTrack(handle);
		m_tracks[handle] = animationTrack;
		
		return animationTrack;
	}
}

void rAnimation::DeleteTrack(unsigned short handle){
	rAnimationTrackMap::iterator result = m_tracks.find(handle);
	
	if (result != m_tracks.end()){
		delete result->second;
		m_tracks.erase(result);
	}
}

size_t rAnimation::NumTracks() const{
	return m_tracks.size();
}
