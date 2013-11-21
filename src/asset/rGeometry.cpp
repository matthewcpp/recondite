#include "rGeometry.hpp"

rGeometry::rGeometry (unsigned int vertexBufferId, size_t vertexElementSize, unsigned int vertexBoneLinkBufferId, bool texCoords, bool normals,
	int assetid, const rString& name, const rString& path)
:rAsset(assetid,name, path)
{
	m_vertexBufferId = vertexBufferId;
	m_vertexBoneLinkBufferId = vertexBoneLinkBufferId;

	m_vertexElementSize = vertexElementSize;
	
	m_hasTexCoords = texCoords;
	m_hasNormals = normals;
}

unsigned int rGeometry::VertexBufferId() const{
	return m_vertexBufferId;
}
unsigned int rGeometry::VertexBoneLinkBufferId() const{
	return m_vertexBoneLinkBufferId;
}

bool rGeometry::HasTexCoords() const{
	return m_hasTexCoords;
}

bool rGeometry::HasNormals() const{
	return m_hasNormals;
}

rAssetType rGeometry::Type() const{
	return rASSET_GEOMETRY;
}

unsigned int rGeometry::ElementBufferCount() const{
	return m_elementBufferIds.size();
}

bool rGeometry::GetElementBuffer(const rString& name, rElementBuffer& elementBuffer) const{
	rElementBufferIdMap::const_iterator result = m_elementBufferIds.find(name);
	
	if (result != m_elementBufferIds.end()){
		elementBuffer = result->second;
		return true;
	}
	else{
		return false;
	}
		
}

bool rGeometry::AddElementBuffer(const rString& name, unsigned int bufferId, size_t elementCount, rGeometryType geometryType){
	rElementBufferIdMap::const_iterator result = m_elementBufferIds.find(name);
	
	if (result == m_elementBufferIds.end()){
		rElementBuffer buffer(bufferId , elementCount, geometryType);
		m_elementBufferIds[name] = buffer;
		return true;
	}
	else{
		return false;
	}
}

void rGeometry::GetElementBufferNames(rArrayString& names) const{
	names.clear();
	
	for (rElementBufferIdMap::const_iterator it = m_elementBufferIds.begin(); it != m_elementBufferIds.end(); ++it)
		names.push_back(it->first);
}

size_t rGeometry::VertexElementSize() const{
	return m_vertexElementSize;
}

const rVertexBoneLinkMap& rGeometry::GetVertexBoneLinks() const{
	return m_vertexBoneLinks;
}

void rGeometry::SetVertexBoneLinks(const rVertexBoneLinkMap& links){
	m_vertexBoneLinks = links;
}
