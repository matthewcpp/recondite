#ifndef R_MODELDATA_HPP
#define R_MODELDATA_HPP

#include <map>
#include <fstream>
#include <utility>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "data/rTexture2DData.hpp"
#include "data/rMaterialData.hpp"
#include "data/rGeometryData.hpp"
#include "data/rGeometryDataFile.hpp"
#include "data/rSkeletonData.hpp"

#include "rSkeleton.hpp"

#include "xml/rXMLDocument.hpp"
#include "xml/rXMLUtil.hpp"

#include "rVertexBoneLink.hpp"

#include "rPath.hpp"
#include "rAlignedBox3.hpp"

struct rMeshData{
	rMeshData(){}
	rMeshData(const rString& n, const rString& buf, const rString& mat);

	rString name;
	rString buffer;
	rString material;
	rAlignedBox3 boundingBox;
};

typedef std::map<rString, rMeshData*> rMeshDataMap;
typedef std::map<rString, rMaterialData*> rMaterialDataMap;
typedef std::map<rString, rTexture2DData*> rTexture2DDataMap;

class rModelData{
public:
	rModelData();
	~rModelData();
	
public:
	void Clear();
	
	size_t MeshCount() const;
	rMeshData* GetMeshData(const rString& name) const;
	rMeshData* CreateMeshData(const rString& name);
	void DeleteMeshData(const rString& name);
	void GetMeshDataNames(rArrayString& names) const;
	
	size_t MaterialCount() const;
	rMaterialData* GetMaterialData(const rString& name) const;
	rMaterialData* CreateMaterialData(const rString& name);
	void DeleteMaterialData(const rString& name);
	void GetMaterialDataNames(rArrayString& names) const;
	
	size_t TextureCount() const;
	rTexture2DData* GetTextureData(const rString& name) const;
	rTexture2DData* CreateTextureData(const rString& name);
	void DeleteTextureData(const rString& name);
	void GetTextureDataNames(rArrayString& names) const;
	
	rGeometryData& GetGeometryData();

	rSkeleton* GetSkeleton() const;
	rSkeleton* CreateSkeleton();

	void SetName(const rString& name);
	rString GetName() const;
	rString GetPath() const;

	rAlignedBox3& GetBoundingBox();

	rContentError WriteToFile(const rString& dir);
	rContentError LoadFromFile(const rString& path);
	rContentError LoadFromStream(std::istream& stream);

private:
	rContentError WriteDependencies(const rString& dir);
	
private:
	rMeshDataMap m_meshes;
	rMaterialDataMap m_materials;
	rTexture2DDataMap m_textures;
	rGeometryData m_geometry;

	rSkeleton* m_skeleton;
	rAlignedBox3 m_boundingBox;

	rString m_name;
	rString m_path;
};

#endif
