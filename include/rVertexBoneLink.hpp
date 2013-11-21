#ifndef R_VERTEXBONELINK_HPP
#define R_VERTEXBONELINK_HPP

#include <map>
#include <vector>

struct rVertexBoneLink{
	rVertexBoneLink(){}
	rVertexBoneLink(unsigned short v, unsigned short b, float w) : vertexIndex(v), boneIndex(b), weight(w) {}

	unsigned short vertexIndex;
	unsigned short boneIndex;
	float weight;
};

typedef std::multimap<unsigned short , rVertexBoneLink> rVertexBoneLinkMap;
typedef std::pair<rVertexBoneLinkMap::const_iterator, rVertexBoneLinkMap::const_iterator> rVertexBoneLinkResult;

#define rMAX_VERTEX_BONE_INFLUENCES 4

struct rVertexBoneData{
	int boneIndex[rMAX_VERTEX_BONE_INFLUENCES];
	float weight[rMAX_VERTEX_BONE_INFLUENCES];
};

typedef std::vector<rVertexBoneData> rVertexBoneDataArray;

#endif
