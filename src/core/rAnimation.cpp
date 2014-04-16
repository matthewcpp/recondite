#include "rAnimation.hpp"

rAnimation::rAnimation(const rString& name){
	m_name = name;
	m_duration = 0.0f;
}

rAnimation::rAnimation(const rString& name, float duration){
	m_name = name;
	m_duration = duration;
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

rAnimationTrack* rAnimation::GetTrack(unsigned short handle) const{
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
float rAnimation::Duration() const{
	return m_duration;
}

void rAnimation::SetDuration(float duration){
	m_duration = duration;
}

void rAnimation::Finalize(){
	for (rAnimationTrackMap::iterator it = m_tracks.begin(); it != m_tracks.end(); ++it)
		it->second->Finalize();
}