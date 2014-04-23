#ifndef R_GEOMETRY_HPP
#define R_GEOMETRY_HPP

#include <map>

#include "rBuild.hpp"
#include "rString.hpp"
#include "rArrayString.hpp"

#include "rAsset.hpp"

#include "rVertexBoneLink.hpp"


class RECONDITE_API rElementBuffer{
public:
	rElementBuffer(unsigned int buffer, size_t sz, rGeometryType t) : m_bufferId(buffer), m_size(sz), m_geometryType(t){}
	
	inline unsigned int BufferId() const {return m_bufferId;}
	inline size_t Size() const {return m_size;}
	inline rGeometryType GeometryType() const {return m_geometryType;}
	
private:
	
	unsigned int m_bufferId;
	size_t m_size;
	rGeometryType m_geometryType;
};

typedef std::map<rString, rElementBuffer*> rElementBufferIdMap;

class RECONDITE_API rGeometry : public rAsset{
public:
	rGeometry (unsigned int vertexBufferId, unsigned int vertexBoneLinkBufferId, int assetid, const rString& name, const rString& path);
	
public:
	unsigned int VertexBufferId() const;
	unsigned int VertexBoneLinkBufferId() const;
	
	size_t ElementBufferCount() const;
	rElementBuffer* GetElementBuffer(const rString& name) const;
	void GetElementBufferNames(rArrayString& names) const;
	rElementBuffer* AddElementBuffer(const rString& name, unsigned int bufferId, size_t elementCount, rGeometryType geometryType);

	const rVertexBoneLinkMap& GetVertexBoneLinks() const;
	void SetVertexBoneLinks(const rVertexBoneLinkMap& links);

	virtual rAssetType Type() const;
private:

	unsigned int m_vertexBufferId; 
	unsigned int m_vertexBoneLinkBufferId;

	rElementBufferIdMap m_elementBufferIds;
	rVertexBoneLinkMap m_vertexBoneLinks;
};

typedef std::map<rString, rGeometry*> rGeometryMap;

#endif
