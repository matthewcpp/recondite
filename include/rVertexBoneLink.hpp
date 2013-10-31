#ifndef R_VERTEXBONELINK_HPP
#define R_VERTEXBONELINK_HPP

#include <map>

struct rVertexBoneLink{
	rVertexBoneLink(){}
	rVertexBoneLink(unsigned short v, unsigned short b, float w) : vertexIndex(v), boneIndex(b), weight(w) {}

	unsigned short vertexIndex;
	unsigned short boneIndex;
	float weight;
};

typedef std::multimap<unsigned short , rVertexBoneLink> rVertexBoneLinkMap;

#endif