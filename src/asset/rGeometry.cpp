#include "rGeometry.hpp"

rGeometry::rGeometry (unsigned int vertexBufferId, unsigned int elementBufferId, bool texCoords, bool normals, 
	int assetid, const rString& name, const rString& path)
:rAsset(assetid,name, path)
{
	m_vertexBufferId = vertexBufferId;
	m_elementBufferId = elementBufferId;
	m_hasTexCoords = texCoords;
	m_hasNormals = normals;
}

unsigned int rGeometry::VertexBufferId() const{
	return m_vertexBufferId;
}

unsigned int rGeometry::ElementBufferId() const{
	return m_elementBufferId;
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
