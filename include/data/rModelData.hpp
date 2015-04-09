#ifndef R_MODELDATA_HPP
#define R_MODELDATA_HPP

#include <map>
#include <fstream>
#include <utility>
#include <memory>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "data/rTexture2DData.hpp"
#include "data/rMaterialData.hpp"
#include "data/rTexCoordGeometryData.hpp"
#include "data/rGeometryDataFile.hpp"
#include "data/rSkeletonData.hpp"

#include "rSkeleton.hpp"

#include "xml/rXMLDocument.hpp"
#include "xml/rXMLUtil.hpp"

#include "rVertexBoneLink.hpp"

#include "rPath.hpp"
#include "rAlignedBox3.hpp"

struct RECONDITE_API rMeshData{
	rMeshData(){}
	rMeshData(const rString& n) : name(n) {}
	rMeshData(const rString& n, const rString& buf, const rString& mat) : name(n), buffer(buf), material(mat) {}

	rString name;
	rString buffer;
	rString material;
	rAlignedBox3 boundingBox;
};

class RECONDITE_API rModelData{
public:
	rModelData();
	
public:
	void Clear();
	
	size_t MeshCount() const;
	rMeshData* GetMeshData(const rString& name) const;
	rMeshData* CreateMeshData(const rString& name);
	void DeleteMeshData(const rString& name);
	void GetMeshDataNames(rArrayString& names) const;

public:
	
	size_t MaterialCount() const;
	rMaterialData* GetMaterialData(const rString& name) const;
	rMaterialData* CreateMaterialData(const rString& name);
	void DeleteMaterialData(const rString& name);
	void GetMaterialDataNames(rArrayString& names) const;

public:
	
	size_t TextureCount() const;
	rTexture2DData* GetTextureData(const rString& name) const;
	rTexture2DData* CreateTextureData(const rString& name);
	void DeleteTextureData(const rString& name);
	void GetTextureDataNames(rArrayString& names) const;

public:
	
	rTexCoordGeometryData* GetGeometryData() const;

	rSkeleton* GetSkeleton() const;
	rSkeleton* CreateSkeleton();

	void SetName(const rString& name);
	rString GetName() const;

	void SetPath(const rString& path);
	rString GetPath() const;

	const rAlignedBox3& GetBoundingBox() const;
	void SetBoundingBox(const rAlignedBox3& boundingBox);

private:

	typedef std::shared_ptr<rMeshData> rMeshDataPtr;
	typedef std::shared_ptr<rTexture2DData> rTextureDataPtr;
	typedef std::shared_ptr<rMaterialData> rMaterialDataPtr;
	typedef std::unique_ptr<rTexCoordGeometryData> rGeometryDataPtr;
	typedef std::unique_ptr<rSkeleton> rSkeletonPtr;

	typedef std::map<rString, rMeshDataPtr> rMeshDataMap;
	typedef std::map<rString, rMaterialDataPtr> rMaterialDataMap;
	typedef std::map<rString, rTextureDataPtr> rTexture2DDataMap;
	
private:
	rMeshDataMap m_meshes;
	rMaterialDataMap m_materials;
	rTexture2DDataMap m_textures;
	rGeometryDataPtr m_geometry;

	rSkeletonPtr m_skeleton;
	rAlignedBox3 m_boundingBox;

	rString m_name;
	rString m_path;

	rNO_COPY_CLASS(rModelData)
};

#endif
