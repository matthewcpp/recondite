#ifndef R_MODELDATA_HPP
#define R_MODELDATA_HPP

#include <map>
#include <vector>
#include <ostream>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAlignedBox3.hpp"

#define R_MODEL_MAGIC_NUMBER 5566
#define R_MODEL_VERSION_NUMBER 1

struct rModelHeader{
	int magicNumber;
	int version;
	size_t numMeshes;
	size_t numMaterials;
	size_t numTextures;
	size_t numGeometryObjects;
};

struct rAssetData{
	rAssetData(const rString& name);
	
	rString m_name;
	
	int m_assignedAssetId;
	rAssetSource m_source;
};

struct rTextureData : public rAssetData{
	rTextureData(const rString& name);
	void OutputTextureData(std::ostream& stream);
};

enum rMaterialTextureType{
	rMATERIAL_TEXTURE_DIFFUSE,
	
	rMATERIAL_TEXTURE_NUM_TYPES
};

typedef std::vector<rTextureData*> rMaterialTextureArray;

struct rMaterialData : public rAssetData{	
	rMaterialData(const rString& name);

	void AddTexture(rTextureData* texture, rMaterialTextureType type);
	
	void OutputMaterialData(std::ostream& stream);
	
	rColor m_color;
	rMaterialTextureArray m_textures;
};

struct rMeshFace{
	unsigned int p0;
	unsigned int p1;
	unsigned int p2;
};

typedef std::vector<rMeshFace> rMeshFaceArray;

struct rGeometryData : rAssetData{
	rGeometryData(const rString& name);

	rVector3Array m_verticies;
	rVector3Array m_normals;
	rVector2Array m_texCoords;
	rMeshFaceArray m_faces;
	
	rAlignedBox3 m_boundingBox;
	
	void ResizeArrays(size_t numVertices, size_t numFaces);
	void ComputeBoundingBox();
	
	size_t NumVertices() const;
	size_t NumFaces() const;
	
	void OutputGeometryData(std::ostream& stream);
};

struct rMeshData : public rAssetData{
	rMeshData(const rString& name, rGeometryData* geometry, rMaterialData* material);
	
	rGeometryData* m_geometry;
	rMaterialData* m_material;
	
	void OutputMeshData(std::ostream& stream);
};

typedef std::vector<rMeshData*> rMeshDataArray;
typedef std::vector<rMaterialData*> rMaterialDataArray;
typedef std::vector<rTextureData*> rTextureDataArray;
typedef std::vector<rGeometryData*> rGeometryDataArray;



class rModelData{
public:
	rModelData();
	~rModelData();
	
	rMeshData* CreateMesh(const rString& name, rGeometryData* geometry, rMaterialData* material);
	rMaterialData* CreateMaterial(const rString& name);
	rTextureData* CreateTexture(const rString& name);
	rGeometryData* CreateGeometry(const rString& name);
	
	
	size_t NumMeshes() const;
	size_t NumMaterials() const;
	size_t NumTextures() const;
	size_t NumGeometry() const;
	
	rMeshData* GetMesh(const rString& name);
	rMaterialData* GetMaterial(const rString& name);
	rTextureData* GetTexture(const rString& name);
	rGeometryData* GetGeometry(const rString& name);
	
	rMeshData* GetMesh(size_t n);
	rMaterialData* GetMaterial(size_t n);
	rTextureData* GetTexture(size_t n);
	rGeometryData* GetGeometry(size_t n);
	
	void DebugOutput(std::ostream& stream);
	
	void Clear();
	
	void SetBasePath(const rString& basePath);
	rString BasePath() const;

private:
	
	rMeshDataArray m_meshes;
	rMaterialDataArray m_materials;
	rTextureDataArray m_textures;
	rGeometryDataArray m_geometry;
	
	rString m_basePath;
};


#endif
