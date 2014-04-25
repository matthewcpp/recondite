#ifndef R_SKELETON_HPP
#define R_SKELETON_HPP

#include <map>
#include <vector>

#include "rBuild.hpp"
#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rVector3.hpp"

#include "rAnimation.hpp"

struct rBone;

typedef std::vector<rBone*> rBoneArray;

struct RECONDITE_API rBone{
public:
	rBone(){}
	rBone(int ID, const rString& n);

public:

	void AddChild(rBone* bone);
	rVector3 WoldPosition() const;
	void CalculateInverseBindTransform();

public:

	int id;
	rBone* parent;
	rString name;
	rVector3 position;
	rQuaternion rotation;

	rBoneArray children;
	rMatrix4 inverseBindTransform;
};

typedef std::map<int, rBone*> rBoneMap;

class RECONDITE_API rSkeleton {
public:
	rSkeleton();
	~rSkeleton();

public:

	rBone* CreateBone(const rString& name);
	rBone* CreateBone(int id, const rString& name);

	rBone* GetBone(const rString& name) const;
	rBone* GetBone(int id) const;

	void GetTopLevelBones(rBoneArray& bones) const;
	void CalculateInverseBoneTransformations();

	size_t NumBones() const;

	void Clear();
	
	rAnimation* CreateAnimation(const rString& name);
	rAnimation* GetAnimation(const rString& name) const;
	void DeleteAnimation(const rString& name);
	size_t NumAnimations() const;
	void GetAnimationNames(rArrayString& names) const;

private:
	void CalculateInverseBoneTransformationsRec(rBone* parent);

private:
	rBoneMap m_bones;
	rAnimationMap m_animations;
};

typedef std::map<rString, rSkeleton*> rSkeletonMap;

#endif
