#include "rAnimationPlayer.hpp"

rAnimationPlayer::rAnimationPlayer(){
	m_animationTime = 0.0f;
	m_skeleton = NULL;
	m_currentAnimation = NULL;
	m_isLooping = false;
}
void rAnimationPlayer::Update(const rTime& time){
	if (m_currentAnimation){
		m_animationTime += time.TimeDeltaSeconds();

		if (m_animationTime > m_currentAnimation->Duration()){
			m_animationTime =  m_currentAnimation->Duration();
		}

		UpdateTransformData();
	}
}

bool rAnimationPlayer::PlayAnimation(const rString& name){
	m_currentAnimation = m_skeleton->GetAnimation(name);

	if (m_currentAnimation){
		m_animationTime = 0.0f;
		memset(&m_keyframeInfo[0], 0, m_keyframeInfo.size() * sizeof (rUnsignedShortArray::value_type));
		UpdateTransformData();
		return true;
	}
	else {
		return false;
	}
}

float rAnimationPlayer::AnimationTime() const{
	return m_animationTime;
}

void rAnimationPlayer::SetSkeleton(rSkeleton* skeleton){
	m_skeleton = skeleton;
	m_animationTime = 0;
	m_currentAnimation = NULL;

	if (m_skeleton){
		size_t numBones = skeleton->NumBones();

		m_transformData.resize(numBones);
		m_keyframeInfo.resize(numBones);

		memset(&m_keyframeInfo[0], 0, m_keyframeInfo.size() * sizeof (rUnsignedShortArray::value_type));
		for (size_t i = 0; i < m_transformData.size(); i++)
			m_transformData[i].LoadIdentity();
	}
}

void rAnimationPlayer::UpdateTransformData(){
	rBoneArray topLevelBones;
	m_skeleton->GetTopLevelBones(topLevelBones);

	for (size_t i = 0; i < topLevelBones.size(); i++){
		UpdateTransformDataRec(NULL, m_skeleton->GetBone(topLevelBones[i]->id));
	}
}

void rAnimationPlayer::UpdateTransformDataRec(rBone* parentBone, rBone* currentBone){
	rAnimationTrack* track = m_currentAnimation->GetTrack(currentBone->id);

	if (track){
		rMatrix4 currentBoneTransform;
		m_keyframeInfo[currentBone->id] = track->InterpolateKeyframe(m_animationTime, currentBoneTransform, m_keyframeInfo[currentBone->id]);

		if (parentBone){
			currentBoneTransform = currentBoneTransform * m_transformData[parentBone->id] ;
		}

		m_transformData[currentBone->id] = currentBoneTransform;

		for (size_t i = 0; i < currentBone->children.size(); i++){
			UpdateTransformDataRec(currentBone, currentBone->children[i]);
		}
	}
}

const rMatrix4Vector& rAnimationPlayer::GetTransformData() const{
	return m_transformData;
}
