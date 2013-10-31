#ifndef R_MODEL_HPP
#define R_MODEL_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"
#include "rGeometry.hpp"
#include "rMaterial.hpp"
#include "rSkeleton.hpp"

#include "rVertexBoneLink.hpp"

struct rMesh {
	rMesh(const rString& n, const rString& buf, rMaterial* mat);
	
	rString name;
	rString buffer;
	rMaterial* material;
};

typedef std::map<rString, rMesh*> rMeshMap;

class rModel : public rAsset{
public:
	rModel(rGeometry* geometry, int assetid, const rString& name, const rString& path);
	~rModel();
	
public:
	rMesh* CreateMesh(const rString& name, const rString& buffer, rMaterial* material);
	rMesh* GetMesh(const rString& name) const;
	void DeleteMesh(const rString& name);
	void GetMeshNames(rArrayString& meshNames) const;
	
	rGeometry* Geometry() const;
	
	size_t NumMeshes() const;
	void Clear();
	
	rSkeleton* Skeleton() const;
	void SetSkeleton(rSkeleton* skeleton);

	virtual rAssetType Type() const;
	
	const rVertexBoneLinkMap& GetVertexBoneLinks() const;
	void SetVertexBoneLinks(const rVertexBoneLinkMap& links);

private:
	rMeshMap m_meshes;
	rGeometry* m_geometry;

	rSkeleton* m_skeleton;
	rVertexBoneLinkMap m_vertexBoneLinks;
};

typedef std::map<rString, rModel*> rModelMap;

#endif
