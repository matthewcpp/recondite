#include "rSkeleton.hpp"

rSkeleton::rSkeleton(){
}

rSkeleton::~rSkeleton(){
	Clear();
}

rBone* rSkeleton::CreateBone(const rString& name){
	int boneId = m_bones.size();

	return CreateBone(boneId, name);
}

rBone* rSkeleton::CreateBone(int id, const rString& name){
	if (m_bones.count(id)){
		return NULL;
	}
	else{
		rBone* bone = new rBone(id, name);
		m_bones[id] = bone;
		return bone;
	}
}

rBone* rSkeleton::GetBone(const rString& name) const{
	for (rBoneMap::const_iterator it = m_bones.begin(); it != m_bones.end(); ++it){
		if (it->second->name == name)
			return it->second;
	}

	return NULL;
}

rBone* rSkeleton::GetBone(int id) const{
	rBoneMap::const_iterator result = m_bones.find(id);

	if (result == m_bones.end()){
		return NULL;
	}
	else{
		return result->second;
	}
}

void rSkeleton::GetTopLevelBones(rBoneArray& bones) const{
	bones.clear();

	for (rBoneMap::const_iterator it = m_bones.begin(); it != m_bones.end(); ++it){
		if (!it->second->parent)
			bones.push_back(it->second);
	}
}

void rSkeleton::Clear(){
	for (rBoneMap::iterator it = m_bones.begin(); it != m_bones.end(); ++it)
		delete it->second;

	m_bones.clear();
}

size_t rSkeleton::NumBones() const{
	return m_bones.size();
}

rAnimation* rSkeleton::CreateAnimation(const rString& name){
	if (m_animations.count(name)){
		return NULL;
	}
	else{
		rAnimation* animation = new rAnimation(name);
		m_animations[name] = animation;
		return animation;
	}
}

rAnimation* rSkeleton::GetAnimation(const rString& name) const{
	rAnimationMap::const_iterator result = m_animations.find(name);
	
	if (result == m_animations.end()){
		return NULL;
	}
	else{
		return result->second;
	}
}

void rSkeleton::DeleteAnimation(const rString& name){
	m_animations.erase(name);
}

size_t rSkeleton::NumAnimations() const{
	return m_animations.size();
}
	
void rSkeleton::GetAnimationNames(rArrayString& names) const{
	names.clear();
	
	for (rAnimationMap::const_iterator it = m_animations.begin(); it != m_animations.end(); ++it)
		names.push_back(it->first);
}

void rSkeleton::CalculateInverseBoneTransformations(){
	rBoneArray topLevelBones;
	GetTopLevelBones(topLevelBones);

	for (size_t i = 0; i < topLevelBones.size(); i++){
		topLevelBones[i]->CalculateInverseBindTransform();
		CalculateInverseBoneTransformationsRec(topLevelBones[i]);
	}
}

void rSkeleton::CalculateInverseBoneTransformationsRec(rBone* parent){
	for (size_t i = 0; i < parent->children.size(); i++){
		parent->children[i]->CalculateInverseBindTransform();
		CalculateInverseBoneTransformationsRec(parent->children[i]);
	}
}
//--------------

rBone::rBone(int ID, const rString& n){
	id = ID;
	name = n;
	parent = NULL;
	position = rVector3::ZeroVector;
	rotation = rQuaternion::Identity;
}

void rBone::AddChild(rBone* bone){
	bone->parent = this;
	children.push_back(bone);
}

rVector3 rBone::WoldPosition() const{
	rVector3 worldPos = position;

	rBone* parentBone = parent;
	while (parentBone){
		worldPos += parentBone->position;
		parentBone = parentBone->parent;
	}

	return worldPos;
}

void rBone::CalculateInverseBindTransform(){
	rMatrix4 rotMatrix, transMatrix, xform;
	rMatrixUtil::QuaterionToMatrix(rotation, rotMatrix);
	transMatrix.SetTranslate(position);

	xform = transMatrix * rotMatrix;
	xform.Invert();

	if (parent)
		inverseBindTransform = parent->inverseBindTransform * xform;
	else
		inverseBindTransform = xform;
}

