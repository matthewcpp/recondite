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

size_t rAnimationTrack::PushKeyframe(float time, const rVector3& translation, rQuaternion& rotation, const rVector3& scale){
	rAnimationKeyframe keyframe(time, translation, rotation, scale);
	m_keyframes.push_back(keyframe);

	return m_keyframes.size();
}

rAnimationKeyframe* rAnimationTrack::GetKeyframe(size_t index) {
	if (index >= m_keyframes.size()){
		return NULL;
	}
	else{
		return &m_keyframes[index];
	}
}

void rAnimationTrack::DetermineKeyframes(float animationTime, unsigned short keyframeHint, unsigned short& start, unsigned short& end) const{
	start = keyframeHint;

	for (size_t i = start + 1; i < m_keyframes.size(); i ++){
			if (animationTime >= m_keyframes[i].time)
				start = i;
			else 
				break;
		}

	if (start == m_keyframes.size() - 1){
		end = start;
	}
	else{
		end = start + 1;
	}
}

unsigned short rAnimationTrack::InterpolateKeyframe(float animationTime, rMatrix4& transform, unsigned short keyframeHint) const{
	rMatrix4 transM, rotM, scaleM;
	rVector3 translate, scale;
	rQuaternion rotate;

	unsigned short start, end;
	DetermineKeyframes(animationTime, keyframeHint, start, end);

	if (start == end){
		translate = m_keyframes[start].translation;
		rotate = m_keyframes[start].rotation;
		scale = m_keyframes[start].scale;
	}
	else {
		const rAnimationKeyframe& prevKey = m_keyframes[start];
		const rAnimationKeyframe& nextKey = m_keyframes[end];
		

		float interpolateVal = rMath::ConvertRange(animationTime, prevKey.time, nextKey.time, 0.0f, 1.0f);
		translate = rVector3::Lerp(prevKey.translation, nextKey.translation, interpolateVal);
		rotate = rQuaternion::Slerp(prevKey.rotation, nextKey.rotation, interpolateVal);
		scale = rVector3::Lerp(prevKey.scale, nextKey.scale, interpolateVal);
	}

	rMatrixUtil::QuaterionToMatrix(rotate, rotM);
	transM.SetTranslate(translate);
	scaleM.SetScale(rVector3::OneVector);
	transform = scaleM * transM * rotM;

	return start;
}

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
