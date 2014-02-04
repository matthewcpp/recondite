#ifndef R_MODEL_HPP
#define R_MODEL_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"
#include "rGeometry.hpp"
#include "rMaterial.hpp"
#include "rSkeleton.hpp"
#include "rAlignedBox3.hpp"

struct rMesh {
	rMesh(const rString& n, const rString& buf, rMaterial* mat, const rAlignedBox3& box);
	
	rString name;
	rString buffer;
	rMaterial* material;
	rAlignedBox3 boundingBox;
};

typedef std::map<rString, rMesh*> rMeshMap;

class rModel : public rAsset{
public:
	rModel(rGeometry* geometry, int assetid, const rString& name, const rString& path);
	~rModel();
	
public:
	rMesh* CreateMesh(const rString& name, const rString& buffer, rMaterial* material, const rAlignedBox3 boundingBox);
	rMesh* GetMesh(const rString& name) const;
	void DeleteMesh(const rString& name);
	void GetMeshNames(rArrayString& meshNames) const;
	
	rGeometry* Geometry() const;
	
	size_t NumMeshes() const;
	void Clear();
	
	rSkeleton* Skeleton() const;
	void SetSkeleton(rSkeleton* skeleton);

	rAlignedBox3 BoundingBox() const;

	virtual rAssetType Type() const;

private:
	rMeshMap m_meshes;
	rGeometry* m_geometry;

	rSkeleton* m_skeleton;
	rAlignedBox3 m_boundingBox;
};

typedef std::map<rString, rModel*> rModelMap;

#endif
