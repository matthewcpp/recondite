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
	rBone(int ID, const rString& n);

public:

	void AddChild(rBone* bone);
	rVector3 WoldPosition() const;

public:

	int id;
	rBone* parent;
	rString name;
	rVector3 position;

	rBoneArray children;
};

typedef std::map<int, rBone*> rBoneMap;

class rSkeleton {
public:
	rSkeleton();
	~rSkeleton();

public:

	rBone* CreateBone(const rString& name);
	rBone* CreateBone(int id, const rString& name);

	rBone* GetBone(const rString& name) const;
	rBone* GetBone(int id) const;

	void GetTopLevelBones(rBoneArray& bones) const;

	size_t NumBones() const;

	void Clear();

private:
	rBoneMap m_bones;
	rBone* m_rootBone;
};

typedef std::map<rString, rSkeleton*> rSkeletonMap;

#endif
