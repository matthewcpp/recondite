#ifndef R_MODEL_HPP
#define R_MODEL_HPP

#include <vector>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"
#include "rMaterial.hpp"

#include "rAlignedBox3.hpp"


class rMesh{
public:
	rMesh(const rString& name, unsigned int vertices, unsigned int normals, unsigned int texCoords, unsigned int indicies, const rAlignedBox3& box, rMaterial* material);
	
	unsigned int Verticies() const;
	unsigned int Normals() const;
	unsigned int TexCoords() const;
	unsigned int Indicies() const;
	
	rMaterial* Material() const;
	void SetMaterial(rMaterial* material);
	
	rString Name() const;
	void SetName(const rString& name);
	
	rAlignedBox3 BoundingBox() const;
	
	rMesh* Clone() const;
	
private:
	unsigned int m_vertices;
	unsigned int m_normals;
	unsigned int m_texCoords;
	unsigned int m_indicies;
	
	rMaterial* m_material;
	
	rString m_name;
	
	rAlignedBox3 m_boundingBox;
};

typedef std::vector<rMesh*> rMeshArray;

class rModel : public rAsset{
public:
	rModel(int assetId , const rString& name);
	~rModel();
	
	size_t NumMeshes() const;
	rMesh* GetMesh(size_t i) const;
	
	rMesh* AddMesh(const rString& name, unsigned int vertices, unsigned int normals, unsigned int texCoords, unsigned int indicies, const rAlignedBox3& box, rMaterial* material);
	
	rModel* Clone() const;
	virtual rAssetType Type() const;
	
private:
	rMeshArray m_meshes;
	rAlignedBox3 m_boundingBox;
};

#endif