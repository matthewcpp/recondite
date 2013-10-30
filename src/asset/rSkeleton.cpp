#include "rSkeleton.hpp"

rSkeleton::rSkeleton(){
	m_rootBone = NULL;
}

rSkeleton::~rSkeleton(){
	Clear();
}

rBone* rSkeleton::CreateBone(const rString& name){
	if (m_bones.count(name)){
		return NULL;
	}
	else{
		rBone* bone = new rBone(name);
		m_bones[name] = bone;
		return bone;
	}
}

rBone* rSkeleton::GetBone(const rString& name) const{
	rBoneMap::const_iterator result = m_bones.find(name);

	if (result == m_bones.end()){
		return NULL;
	}
	else{
		return result->second;
	}
}

void rSkeleton::GetBoneNames(rArrayString& names) const{
	names.clear();

	for (rBoneMap::const_iterator it = m_bones.begin(); it != m_bones.end(); ++it)
		names.push_back(it->first);
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

//--------------

rBone::rBone(const rString& n){
	name = n;
	parent = NULL;
	position = rVector3::ZeroVector;
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

