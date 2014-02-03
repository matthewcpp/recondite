#include "rGeometry.hpp"

rGeometry::rGeometry (unsigned int vertexBufferId, unsigned int vertexBoneLinkBufferId, int assetid, const rString& name, const rString& path)
:rAsset(assetid,name, path)
{
	m_vertexBufferId = vertexBufferId;
	m_vertexBoneLinkBufferId = vertexBoneLinkBufferId;
}

unsigned int rGeometry::VertexBufferId() const{
	return m_vertexBufferId;
}
unsigned int rGeometry::VertexBoneLinkBufferId() const{
	return m_vertexBoneLinkBufferId;
}

rAssetType rGeometry::Type() const{
	return rASSET_GEOMETRY;
}

unsigned int rGeometry::ElementBufferCount() const{
	return m_elementBufferIds.size();
}

rElementBuffer* rGeometry::GetElementBuffer(const rString& name) const{
	rElementBufferIdMap::const_iterator result = m_elementBufferIds.find(name);
	
	if (result != m_elementBufferIds.end()){
		return result->second;
	}
	else{
		return false;
	}
		
}

rElementBuffer* rGeometry::AddElementBuffer(const rString& name, unsigned int bufferId, size_t elementCount, rGeometryType geometryType){	
	if (m_elementBufferIds.count(name)){
		return NULL;
	}
	else{
		rElementBuffer* buffer = new rElementBuffer(bufferId , elementCount, geometryType);
		m_elementBufferIds[name] = buffer;
		return buffer;
	}
}

void rGeometry::GetElementBufferNames(rArrayString& names) const{
	names.clear();
	
	for (rElementBufferIdMap::const_iterator it = m_elementBufferIds.begin(); it != m_elementBufferIds.end(); ++it)
		names.push_back(it->first);
}

const rVertexBoneLinkMap& rGeometry::GetVertexBoneLinks() const{
	return m_vertexBoneLinks;
}

void rGeometry::SetVertexBoneLinks(const rVertexBoneLinkMap& links){
	m_vertexBoneLinks = links;
}
