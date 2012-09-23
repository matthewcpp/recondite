#include "rModelData.hpp"

//-------------------------------------------------

rAssetData::rAssetData(const rString& name){
	m_name = name;
	m_assignedAssetId = 0;
	m_source = rASSET_SOURCE_INTERNAL;
}

//-------------------------------------------------

rTextureData::rTextureData(const rString& name)
:rAssetData(name)
{

}

void rTextureData::OutputTextureData(std::ostream& stream){
	stream << "Texture: " << m_name << '\n';
}

//-------------------------------------------------

rMaterialData::rMaterialData(const rString& name)
:rAssetData(name)
{
	m_color.Set(255,255,255,255);
	m_textures.assign(rMATERIAL_TEXTURE_NUM_TYPES, NULL);
}

void rMaterialData::OutputMaterialData(std::ostream& stream){
	stream << "Material: " << m_name << '\n';
	stream << "\tTextures:\n";
	
	stream <<std::endl;
}

void rMaterialData::AddTexture(rTextureData* texture, rMaterialTextureType type){
	m_textures[type] = texture;
}

//-------------------------------------------------

rGeometryData::rGeometryData(const rString& name)
:rAssetData(name)
{
	m_boundingBox = rAlignedBox3::NullBox;
}

void rGeometryData::ResizeArrays(size_t numVertices, size_t numFaces){
	m_verticies.resize(numVertices);
	m_normals.resize(numVertices);
	m_texCoords.resize(numVertices);
	m_faces.resize(numFaces);
}

size_t rGeometryData::NumVertices() const{
	return m_verticies.size();
}

size_t rGeometryData::NumFaces() const{
	return m_faces.size();
}

void rGeometryData::ComputeBoundingBox(){
	m_boundingBox.Empty();
	
	for (size_t i =0; i < m_verticies.size(); i++)
		m_boundingBox.AddPoint(m_verticies[i]);
}

void rGeometryData::OutputGeometryData(std::ostream& stream){
	stream << "Mesh: " << m_name << '\n';
	stream << "\tVerticies: " << m_verticies.size();
	stream << "\tFaces: " << m_faces.size();
	stream << "\tMaterial: ";
}

//-------------------------------------------------

rMeshData::rMeshData(const rString& name, rGeometryData* geometry, rMaterialData* material)
:rAssetData(name)
{
	m_material = material;
	m_geometry = geometry;
}

void rMeshData::OutputMeshData(std::ostream& stream){
	stream << "Mesh: " << m_name << '\n';
	stream << "\tMaterial: ";
	
	if (m_material)
		stream << m_material->m_name;
	
	stream <<std::endl;
}

//-------------------------------------------------

rModelData::rModelData(){
}

rModelData::~rModelData(){
	Clear();
}

void rModelData::Clear(){
	for (size_t i = 0; i < m_meshes.size(); i++)
		delete m_meshes[i];
	
	for (size_t i = 0; i < m_materials.size(); i++)
		delete m_materials[i];
	
	for (size_t i = 0; i < m_textures.size(); i++)
		delete m_textures[i];
	
	for (size_t i = 0; i < m_geometry.size(); i++)
		delete m_geometry[i];
	
	m_meshes.clear();
	m_materials.clear();
	m_textures.clear();
	m_geometry.clear();
}

rMeshData* rModelData::CreateMesh(const rString& name, rGeometryData* geometry, rMaterialData* material){
	rMeshData* mesh = new rMeshData(name, geometry, material);
	m_meshes.push_back(mesh);
	return mesh;
}

rMaterialData* rModelData::CreateMaterial(const rString& name){
	rMaterialData* material = new rMaterialData(name);
	m_materials.push_back(material);
	
	return material;
}

rTextureData* rModelData::CreateTexture(const rString& name){
	rTextureData* texture = new rTextureData(name);
	m_textures.push_back(texture);
	
	return texture;
}

rGeometryData* rModelData::CreateGeometry(const rString& name){
	rGeometryData* geometry = new rGeometryData(name);
	m_geometry.push_back(geometry);
	return geometry;
}

size_t rModelData::NumMeshes() const{
	return m_meshes.size();
}

size_t rModelData::NumMaterials() const{
	return m_materials.size();
}

size_t rModelData::NumTextures() const{
	return m_textures.size();
}

size_t rModelData::NumGeometry() const{
	return m_geometry.size();
}

rMeshData* rModelData::GetMesh(size_t n){
	if (n >= m_meshes.size())
		return NULL;
	
	return m_meshes[n];
}

rMaterialData* rModelData::GetMaterial(size_t n){
	if (n >= m_materials.size())
		return NULL;
	
	return m_materials[n];
}

rTextureData* rModelData::GetTexture(size_t n){
	if (n >= m_textures.size())
		return NULL;
	
	return m_textures[n];
}

rMeshData* rModelData::GetMesh(const rString& name){
	for (size_t i = 0; i < m_meshes.size(); i++){
		if (m_meshes[i]->m_name == name)
			return m_meshes[i];
	}
	
	return NULL;
}

rMaterialData* rModelData::GetMaterial(const rString& name){
	for (size_t i = 0; i < m_materials.size(); i++){
		if (m_materials[i]->m_name == name)
			return m_materials[i];
	}
	
	return NULL;
}

rTextureData* rModelData::GetTexture(const rString& name){
	for (size_t i = 0; i < m_textures.size(); i++){
		if (m_textures[i]->m_name == name)
			return m_textures[i];
	}
	
	return NULL;
}

rGeometryData* rModelData::GetGeometry(const rString& name){
	for (size_t i = 0; i < m_geometry.size(); i++){
		if (m_geometry[i]->m_name == name)
			return m_geometry[i];
	}
	
	return NULL;
}

void rModelData::DebugOutput(std::ostream& stream){
	stream << "Model Data:\n"<<std::endl;
	
	for (size_t i = 0; i < m_materials.size(); i++)
		m_materials[i]->OutputMaterialData(stream);
	
		for (size_t i = 0; i < m_meshes.size(); i++)
		m_meshes[i]->OutputMeshData(stream);
}

void rModelData::SetBasePath(const rString& basePath){
	m_basePath = basePath;
}

rString rModelData::BasePath() const{
	return m_basePath;
}
