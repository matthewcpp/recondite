#include "rModel.hpp"

rModel::rModel(rGeometry* geometry, int assetid, const rString& name, const rString& path)
:rAsset(assetid, name, path)
{
	m_geometry = geometry;
	m_skeleton = NULL;

	m_boundingBox.Invalidate();
}

rModel::~rModel(){
	Clear();
}
	
rMesh* rModel::CreateMesh(const rString& name, const rString& buffer, rGeometryType geometryType , rMaterial* material, const rAlignedBox3 boundingBox){
	if (m_meshes.count(name)){
		return NULL;
	}
	else{
		rMesh* mesh = new rMesh(name, buffer, geometryType, boundingBox);
		mesh->geometry = m_geometry;
		mesh->Drawable()->SetMaterial(material);

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

rAssetType rModel::Type() const{
	return rASSET_MODEL;
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


//-----------------------
rMesh::rMesh(const rString& n, const rString& buf, rGeometryType geo, const rAlignedBox3& box){
	name = n;
	buffer = buf;
	boundingBox = box;
	geometryType = geo;
}
