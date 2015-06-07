#include "asset/rModel.hpp"

//---------------rMesh

rMesh::rMesh(const rString& n, const rString& buf, rGeometryType geo, const rAlignedBox3& box, rMaterial* material){
	m_name = n;
	m_buffer = buf;
	m_boundingBox = box;
	m_geometryType = geo;
	m_material = material;
}

rString rMesh::Name() const{
	return m_name;
}

rString rMesh::Buffer() const{
	return m_buffer;
}

rAlignedBox3 rMesh::BoundingBox() const{
	return m_boundingBox;
}

rGeometryType rMesh::GeometryType() const{
	return m_geometryType;
}

rMaterial* rMesh::Material() const{
	return m_material;
}

//---------------rModel


rModel::rModel(const rString& name, rGeometry* geometry){
	m_geometry = geometry;
	m_skeleton = NULL;

	m_boundingBox.Invalidate();
	m_name = name;
}

rModel::~rModel(){
	Clear();
}
	
rMesh* rModel::CreateMesh(const rString& name, const rString& buffer, rGeometryType geometryType , rMaterial* material, const rAlignedBox3 boundingBox){
	if (m_meshes.count(name)){
		return NULL;
	}
	else{
		rMesh* mesh = new rMesh(name, buffer, geometryType, boundingBox, material);
		m_meshes[name] = mesh;

		m_boundingBox.AddBox(boundingBox);
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

void rModel::GetMeshNames(rArrayString& meshNames) const{
	meshNames.clear();
	
	for (rMeshMap::const_iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
		meshNames.push_back(it->first);
}

rSkeleton* rModel::Skeleton() const{
	return m_skeleton;
}

void rModel::SetSkeleton(rSkeleton* skeleton){
	m_skeleton = skeleton;
}
rAlignedBox3 rModel::BoundingBox() const{
	return m_boundingBox;
}

rString rModel::Name() const{
	return m_name;
}