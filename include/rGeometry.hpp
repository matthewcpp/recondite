#ifndef R_GEOMETRY_HPP
#define R_GEOMETRY_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"

#include "rVertexBoneLink.hpp"

class rElementBuffer{
public:
	rElementBuffer() : bufferId(0), size(0), geometryType(rGEOMETRY_TRIANGLES){}
	rElementBuffer(unsigned int buffer, size_t sz, rGeometryType t) : bufferId(buffer), size(sz), geometryType(t){}
	
	unsigned int BufferId() const {return bufferId;}
	size_t Size() const {return size;}
	rGeometryType GeometryType() const {return geometryType;}
	
private:
	
	unsigned int bufferId;
	size_t size;
	rGeometryType geometryType;
};

typedef std::map<rString, rElementBuffer> rElementBufferIdMap;

class rGeometry : public rAsset{
public:
	rGeometry (unsigned int vertexBufferId, size_t vertexElementSize, unsigned int vertexBoneLinkBufferId, bool texCoords, bool normals,
		int assetid, const rString& name, const rString& path);
	
public:
	unsigned int VertexBufferId() const;
	unsigned int VertexBoneLinkBufferId() const;
	
	size_t ElementBufferCount() const;
	bool GetElementBuffer(const rString& name, rElementBuffer& elementBuffer) const;
	void GetElementBufferNames(rArrayString& names) const;
	bool AddElementBuffer(const rString& name, unsigned int bufferId, size_t elementCount, rGeometryType geometryType);
	
	bool HasTexCoords() const;
	bool HasNormals() const;
	
	size_t VertexElementSize() const;

	const rVertexBoneLinkMap& GetVertexBoneLinks() const;
	void SetVertexBoneLinks(const rVertexBoneLinkMap& links);

	virtual rAssetType Type() const;
private:

	unsigned int m_vertexBufferId; 
	unsigned int m_vertexBoneLinkBufferId;

	bool m_hasTexCoords; 
	bool m_hasNormals;
	
	size_t m_vertexElementSize;

	rElementBufferIdMap m_elementBufferIds;
	rVertexBoneLinkMap m_vertexBoneLinks;
};

typedef std::map<rString, rGeometry*> rGeometryMap;

#endif
