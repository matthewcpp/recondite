#include "data/rModelData.hpp"

rModelData::rModelData(){
	m_skeleton = NULL;
}

rModelData::~rModelData(){
	Clear();
}

void rModelData::Clear(){
	for (rMeshDataMap::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
		delete it->second;
	
	for (rMaterialDataMap::iterator it = m_materials.begin(); it!= m_materials.end(); ++it)
		delete it->second;
	
	for (rTexture2DDataMap::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
		delete it->second;
	
	m_geometry.Clear();
	m_meshes.clear();
	m_materials.clear();
	m_textures.clear();

	m_name.clear();
	m_path.clear();

	m_boundingBox.Empty();

	if (m_skeleton){
		delete m_skeleton;
		m_skeleton = NULL;
	}
}

size_t rModelData::MeshCount() const{
	return m_meshes.size();
}

rMeshData* rModelData::GetMeshData(const rString& name) const{
	rMeshData* meshData = NULL;
	
	rMeshDataMap::const_iterator result = m_meshes.find(name);
	
	if (result != m_meshes.end()){
		meshData = result->second;
	}
	
	return meshData;
}

rMeshData* rModelData::CreateMeshData(const rString& name){
	if (m_meshes.count(name)){
		return NULL;
	}
	else{
		rMeshData* meshData = new rMeshData();
		meshData->name = name;
		m_meshes[name] = meshData;
		
		return meshData;
	}
}

void rModelData::DeleteMeshData(const rString& name){
	m_meshes.erase(name);
}

void rModelData::GetMeshDataNames(rArrayString& names) const{
	names.clear();

	for (rMeshDataMap::const_iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
		names.push_back(it->first);
}

size_t rModelData::MaterialCount() const{
	return m_materials.size();
}

rMaterialData* rModelData::GetMaterialData(const rString& name) const{
	rMaterialData* materialData = NULL;
	
	rMaterialDataMap::const_iterator result = m_materials.find(name);
	
	if (result != m_materials.end())
		materialData = result->second;
	
	return materialData;
}

rMaterialData* rModelData::CreateMaterialData(const rString& name){
	if (m_materials.count(name)){
		return NULL;
	}
	else{
		rMaterialData* materialData = new rMaterialData();
		m_materials[name] = materialData;
		
		return materialData;
	}
}

void rModelData::DeleteMaterialData(const rString& name){
	m_materials.erase(name);
}

void rModelData::GetMaterialDataNames(rArrayString& names) const{
	names.clear();
	
	for (rMaterialDataMap::const_iterator it = m_materials.begin(); it!= m_materials.end(); ++it)
		names.push_back(it->first);
}

size_t rModelData::TextureCount() const{
	return m_textures.size();
}

rTexture2DData* rModelData::GetTextureData(const rString& name) const{
	rTexture2DData* textureData = NULL;
	
	rTexture2DDataMap::const_iterator result= m_textures.find(name);
	
	if (result != m_textures.end()){
		textureData = result->second;
	}
	
	return textureData;
}

rTexture2DData* rModelData::CreateTextureData(const rString& name){
	if (m_textures.count(name)){
		return NULL;
	}
	else{
		rTexture2DData* textureData = new rTexture2DData();
		m_textures[name] = textureData;
		return textureData;
	}
}

void rModelData::DeleteTextureData(const rString& name){
	m_textures.erase(name);
}

void rModelData::GetTextureDataNames(rArrayString& names) const{
	names.clear();
	
	for (rTexture2DDataMap::const_iterator it = m_textures.begin(); it != m_textures.end(); ++it)
		names.push_back(it->first);
}

rGeometryData& rModelData::GetGeometryData(){
	return m_geometry;
}

rContentError rModelData::LoadFromStream(std::istream& stream){
	Clear();

	rXMLDocument document;
	document.LoadFromStream(stream);

	m_name = document.GetRoot()->GetFirstChildNamed("name")->Text();
	rXMLUtil::ReadAlignedBox3FromFromElement(document.GetRoot()->GetFirstChildNamed("boundingBox"), m_boundingBox);
	
	rXMLElement* meshesNode = document.GetRoot()->GetFirstChildNamed("meshes");

	for (size_t i = 0; i < meshesNode->NumChildren(); i++){
		rXMLElement* meshNode = meshesNode->GetChild(i);

		rMeshData* meshData= new rMeshData(meshNode->GetFirstChildNamed("name")->Text(), meshNode->GetFirstChildNamed("buffer")->Text(), meshNode->GetFirstChildNamed("material")->Text());
		rXMLUtil::ReadAlignedBox3FromFromElement(meshNode->GetFirstChildNamed("boundingBox"), meshData->boundingBox);
		m_meshes[meshData->name] = meshData;
	}
	
	return rCONTENT_ERROR_NONE;
}

rContentError rModelData::LoadFromFile(const rString& path){
	std::ifstream file (path.c_str());
	rContentError error =  LoadFromStream(file);
	m_path = path;

	return error;
}

rContentError rModelData::WriteDependencies(const rString& dir){
	m_geometry.WriteToFile(rPath::Assemble(dir, m_name, "rgeo"));

	for (rTexture2DDataMap::iterator it = m_textures.begin(); it != m_textures.end(); ++it){
		it->second->WriteToPath(rPath::Assemble(dir, it->first, "rtex"));
	}

	for (rMaterialDataMap::iterator it = m_materials.begin(); it!= m_materials.end(); ++it){
		it->second->WriteToPath(rPath::Assemble(dir, it->first, "rmat"));
	}

	if (m_skeleton){
		rSkeletonData skeletonData;
		skeletonData.WriteToFile(rPath::Assemble(dir, m_name, "rskl"), *m_skeleton);
	}

	return rCONTENT_ERROR_NONE;
}

rContentError rModelData::WriteToFile(const rString& dir){
	rXMLDocument document;
	document.CreateRoot("model");
	document.GetRoot()->CreateChild("name", m_name);
	rXMLUtil::CreateAlignedBox3Element(document.GetRoot(), "boundingBox", m_boundingBox);

	if (m_skeleton)
		document.GetRoot()->CreateChild("skeleton", m_name);

	WriteDependencies (dir);
	rXMLElement* meshes = document.GetRoot()->CreateChild("meshes");

	for (rMeshDataMap::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it){
		rMeshData* meshData = it->second;

		rXMLElement* meshNode = meshes->CreateChild("mesh");
		meshNode->CreateChild<rString>("name",meshData->name);
		meshNode->CreateChild("material", meshData->material);
		meshNode->CreateChild("buffer", meshData->buffer);

		rXMLUtil::CreateAlignedBox3Element(meshNode, "boundingBox", meshData->boundingBox);
	}

	document.WriteToFile(rPath::Assemble(dir, m_name, "rmdl"));

	return rCONTENT_ERROR_NONE;
}

void rModelData::SetName(const rString& name){
	m_name = name;
}

rString rModelData::GetName() const{
	return m_name;
}

rString rModelData::GetPath() const{
	return m_path;
}

rSkeleton* rModelData::GetSkeleton() const{
	return m_skeleton;
}

rSkeleton* rModelData::CreateSkeleton(){
	if (m_skeleton){
		return NULL;
	}
	else{
		m_skeleton = new rSkeleton();
		return m_skeleton;
	}
}

rAlignedBox3& rModelData::GetBoundingBox(){
	return m_boundingBox;
}

//---------------------
rMeshData::rMeshData(const rString& n, const rString& buf, const rString& mat){
	name = n;
	buffer = buf;
	material = mat;
}