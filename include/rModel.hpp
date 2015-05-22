#ifndef R_MODEL_HPP
#define R_MODEL_HPP

#include <map>
#include <memory>

#include "rBuild.hpp"
#include "rTypes.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "rAsset.hpp"
#include "rGeometry.hpp"
#include "rMaterial.hpp"
#include "rSkeleton.hpp"
#include "rAlignedBox3.hpp"

class RECONDITE_API rMesh {
public:
	rMesh(const rString& n, const rString& buf, rGeometryType geo, const rAlignedBox3& box, rMaterial* material);

public:
	rString Name() const;
	rString Buffer() const;
	rAlignedBox3 BoundingBox() const;
	rGeometryType GeometryType() const;
	
	rMaterial* Material() const;

private:

	rString m_name;
	rString m_buffer;
	rAlignedBox3 m_boundingBox;
	rGeometryType m_geometryType;
	rMaterial* m_material;
};



typedef std::map<rString, rMesh*> rMeshMap;

class RECONDITE_API rModel : public rAsset{
public:
	rModel(rGeometry* geometry, int assetid, const rString& name, const rString& path);
	~rModel();
	
public:
	rMesh* CreateMesh(const rString& name, const rString& buffer, rGeometryType geometryType, rMaterial* material, const rAlignedBox3 boundingBox);
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
