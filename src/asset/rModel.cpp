#include "rModel.hpp"

rMesh::rMesh(const rString& name, unsigned int vertices, unsigned int normals, unsigned int texCoords, unsigned int indicies, const rAlignedBox3& box, rMaterial* material)
{
	m_vertices = vertices;
	m_normals = normals;
	m_texCoords = texCoords;
	m_indicies = indicies;
	
	m_material = material;
	m_name = name;
	m_boundingBox = box;
}

unsigned int rMesh::Verticies() const{
	return m_vertices;
}

unsigned int rMesh::Normals() const{
	return m_normals;
}

unsigned int rMesh::TexCoords() const{
	return m_texCoords;
}

unsigned int rMesh::Indicies() const{
	return m_indicies;
}

rMaterial* rMesh::Material() const{
	return m_material;
}

void rMesh::SetMaterial(rMaterial* material){
	m_material = material;
}

rString rMesh::Name() const{
	return m_name;
}

void rMesh::SetName(const rString& name){
	m_name = name;
}

rAlignedBox3 rMesh::BoundingBox() const{
	return m_boundingBox;
}

rMesh* rMesh::Clone() const{
	return new rMesh(m_name , m_vertices, m_normals, m_texCoords, m_indicies, m_boundingBox, m_material);
}


//===============================================

rModel::rModel(int assetId , const rString& name)
:rAsset(assetId, name)
{
	
}

rModel::~rModel(){
	for (size_t i =0; i < m_meshes.size(); i++)
		delete m_meshes[i];
	
	m_meshes.clear();
}

rMesh* rModel::AddMesh(const rString& name, unsigned int vertices, unsigned int normals, unsigned int texCoords, unsigned int indicies, const rAlignedBox3& box, rMaterial* material){
	rMesh* mesh = new rMesh(name , vertices, normals, texCoords, indicies, box, material);
	
	m_meshes.push_back(mesh);
	m_boundingBox.AddBox(box);
	
	return mesh;
}

rModel* rModel::Clone() const{
	rModel* clone = new rModel(m_assetId, m_name);
	
	clone->m_boundingBox = m_boundingBox;
	
	for (size_t i = 0; i < m_meshes.size(); i++)
		clone->m_meshes.push_back(m_meshes[i]->Clone());
	
	return clone;
}

rMesh* rModel::GetMesh(size_t i) const{
	if (i >= m_meshes.size())
		return NULL;
	
	return m_meshes[i];
}

size_t rModel::NumMeshes() const{
	return m_meshes.size();
}

rAssetType rModel::Type() const{
	return rASSET_MODEL;
}
