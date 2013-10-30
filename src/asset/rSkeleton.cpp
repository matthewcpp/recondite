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

rBone* rSkeleton::GetRootBone() const{
	return m_rootBone;
}

rBone* rSkeleton::SetRootBone(const rString& name){
	rBone* root = GetBone(name);

	m_rootBone = root;

	return m_rootBone;
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

