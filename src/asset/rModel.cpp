#include "rModel.hpp"

rModel::rModel(rGeometry* geometry, int assetid, const rString& name, const rString& path)
:rAsset(assetid, name, path)
{
	m_geometry = geometry;
}

rModel::~rModel(){
	Clear();
}
	
rMesh* rModel::CreateMesh(const rString& name, const rString& buffer, rMaterial* material){
	if (m_meshes.count(name)){
		return NULL;
	}
	else{
		rMesh* mesh = new rMesh(name, buffer, material);
		m_meshes[name] = mesh;
		return mesh;
	}
}

rMesh* rModel::GetMesh(const rString& name) const{
	rMeshMap::const_iterator result = m_meshes.find(name);
	
	if (result == m_meshes.end()){
		return NULL;
	}
	else{
		return result->second;
	}
}

void rModel::DeleteMesh(const rString& name){
	m_meshes.erase(name);
}

size_t rModel::NumMeshes() const{
	return m_meshes.size();
}

void rModel::Clear(){
	for(rMeshMap::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it){
		delete it->second;
	}
	
	m_meshes.clear();
}

rGeometry* rModel::Geometry() const{
	return m_geometry;
}

rAssetType rModel::Type() const{
	return rASSET_GEOMETRY;
}

void rModel::GetMeshNames(rArrayString& meshNames) const{
	meshNames.clear();
	
	for (rMeshMap::const_iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
		meshNames.push_back(it->first);
}

//-----------------------
rMesh::rMesh(const rString& n, const rString& buf, rMaterial* mat){
	name = n;
	buffer = buf;
	material = mat;
}
