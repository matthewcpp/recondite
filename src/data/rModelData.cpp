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
	m_vertexBoneLinks.clear();

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

const rVertexBoneLinkMap& rModelData::GetBoneLinks() const{
	return m_vertexBoneLinks;
}

size_t rModelData::NumVertexBoneLinks() const{
	return m_vertexBoneLinks.size();
}

void rModelData::CreateVertexBoneLink(unsigned short vertexIndex, unsigned short boneIndex, float weight){
	rVertexBoneLink link(vertexIndex, boneIndex, weight);

	m_vertexBoneLinks.insert(std::make_pair(vertexIndex, link));
}

rContentError rModelData::LoadFromStream(std::istream& stream){
	Clear();

	rXMLDocument document;
	document.LoadFromStream(stream);

	m_name = document.GetRoot()->GetFirstChildNamed("name")->Text();
	
	rXMLElement* meshesNode = document.GetRoot()->GetFirstChildNamed("meshes");

	for (size_t i = 0; i < meshesNode->NumChildren(); i++){
		rXMLElement* meshNode = meshesNode->GetChild(i);

		rMeshData* meshData= new rMeshData(meshNode->GetFirstChildNamed("name")->Text(), meshNode->GetFirstChildNamed("buffer")->Text(), meshNode->GetFirstChildNamed("material")->Text());
		m_meshes[meshData->name] = meshData;
	}

	rXMLElement* vertexBoneLinks = document.GetRoot()->GetFirstChildNamed("vertexBoneLinks");
	rVertexBoneLink link;
	for (size_t i = 0; i < vertexBoneLinks->NumChildren(); i++){
		rXMLElement* linkNode = vertexBoneLinks->GetChild(i);
		linkNode->GetAttribute<unsigned short>("bone", link.boneIndex);
		linkNode->GetAttribute<unsigned short>("vertex", link.vertexIndex);
		linkNode->GetAttribute<float>("weight", link.weight);

		m_vertexBoneLinks.insert(std::make_pair(link.vertexIndex, link));
	}
	
	return rCONTENT_ERROR_NONE;
}

rContentError rModelData::LoadFromFile(const rString& path){
	std::ifstream file (path.c_str());

	return LoadFromStream(file);
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

	if (m_skeleton)
		document.GetRoot()->CreateChild("skeleton", m_name);

	WriteDependencies (dir);
	rXMLElement* meshes = document.GetRoot()->CreateChild("meshes");

	for (rMeshDataMap::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it){
		rXMLElement* meshNode = meshes->CreateChild("mesh");
		meshNode->CreateChild<rString>("name", it->first);
		meshNode->CreateChild("material", it->second->material);
		meshNode->CreateChild("buffer", it->second->buffer);
	}

	rXMLElement* vertexBoneLinks = document.GetRoot()->CreateChild("vertexBoneLinks");

	for (rVertexBoneLinkMap::const_iterator it = m_vertexBoneLinks.begin(); it != m_vertexBoneLinks.end(); ++it){
		rXMLElement* element = vertexBoneLinks->CreateChild("link");
		const rVertexBoneLink& link = it->second;
		
		element->AddAttribute<unsigned short>("vertex", link.vertexIndex);
		element->AddAttribute<unsigned short>("bone", link.boneIndex);
		element->AddAttribute<float>("weight", link.weight);
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

//---------------------
rMeshData::rMeshData(const rString& n, const rString& buf, const rString& mat){
	name = n;
	buffer = buf;
	material = mat;
}