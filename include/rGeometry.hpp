#ifndef R_GEOMETRY_HPP
#define R_GEOMETRY_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"

class rElementBuffer{
public:
	rElementBuffer() : bufferId(0), size(0){}
	rElementBuffer(unsigned int buffer, size_t sz) : bufferId(buffer), size(sz){}
	
	unsigned int BufferId() const {return bufferId;}
	size_t Size() const {return size;};
	
private:
	
	unsigned int bufferId;
	size_t size;
};

typedef std::map<rString, rElementBuffer> rElementBufferIdMap;

class rGeometry : public rAsset{
public:
	rGeometry (unsigned int vertexBufferId, bool texCoords, bool normals, 
		int assetid, const rString& name, const rString& path);
	
public:
	unsigned int VertexBufferId() const;
	
	size_t ElementBufferCount() const;
	bool GetElementBuffer(const rString& name, rElementBuffer& elementBuffer) const;
	void GetElementBufferNames(rArrayString& names) const;
	bool AddElementBuffer(const rString& name, unsigned int bufferId, size_t elementCount);
	
	bool HasTexCoords() const;
	bool HasNormals() const;
	
	virtual rAssetType Type() const;
private:

	unsigned int m_vertexBufferId; 
	bool m_hasTexCoords; 
	bool m_hasNormals;
	
	rElementBufferIdMap m_elementBufferIds;
	
};

typedef std::map<rString, rGeometry*> rGeometryMap;

#endif
