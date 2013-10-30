#ifndef R_SKELETON_HPP
#define R_SKELETON_HPP

#include <map>
#include <vector>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rVector3.hpp"

struct rBone;

typedef std::vector<rBone*> rBoneArray;

struct rBone{
public:
	rBone(){}
	rBone(const rString& n);

	void AddChild(rBone* bone);
	rVector3 WoldPosition() const;

	rBone* parent;
	rString name;
	rVector3 position;

	rBoneArray children;
};

typedef std::map<rString, rBone*> rBoneMap;

class rSkeleton {
public:
	rSkeleton();
	~rSkeleton();

public:

	rBone* CreateBone(const rString& name);
	rBone* GetBone(const rString& name) const;
	void GetBoneNames(rArrayString& names) const;
	void GetTopLevelBones(rBoneArray& bones) const;
	size_t NumBones() const;

	void Clear();

private:
	rBoneMap m_bones;
	rBone* m_rootBone;
};

typedef std::map<rString, rSkeleton*> rSkeletonMap;

#endif
