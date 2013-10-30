#include "rSkeleton.hpp"

rSkeleton::rSkeleton(){
	m_rootBone = NULL;
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

//--------------

rBone::rBone(int ID, const rString& n){
	id = ID;
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

