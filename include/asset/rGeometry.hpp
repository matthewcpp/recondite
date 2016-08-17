#ifndef R_GEOMETRY_HPP
#define R_GEOMETRY_HPP

#include <map>

#include "rBuild.hpp"
#include "rTypes.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "rVertexBoneLink.hpp"

namespace recondite {
	class RECONDITE_API Geometry {
	public:
		Geometry() : _bufferId(0), _hasNormals(false), _hasTexCoords(false) {}

		Geometry(uint32_t bufferId, uint32_t vertexCount, bool hasNormals, bool hasTexCoords)
			: _bufferId(bufferId), _vertexCount(vertexCount), _hasNormals(hasNormals), _hasTexCoords(hasTexCoords) {}

	public:
		inline uint32_t GetBufferId() const;
		inline uint32_t GetVertexCount() const;
		inline bool GetHasNormals() const;
		inline bool GetHasTexCoords() const;

	private:
		uint32_t _bufferId;
		uint32_t _vertexCount;
		bool _hasNormals;
		bool _hasTexCoords;
	};


	inline uint32_t Geometry::GetBufferId() const {
		return _bufferId;
	}

	inline uint32_t Geometry::GetVertexCount() const {
		return _vertexCount;
	}

	inline bool Geometry::GetHasNormals() const {
		return _hasNormals;
	}

	inline bool Geometry::GetHasTexCoords() const {
		return _hasTexCoords;
	}
}



class RECONDITE_API rElementBuffer{
public:
	rElementBuffer(unsigned int buffer, size_t sz, rGeometryType t) : m_bufferId(buffer), m_size(sz), m_geometryType(t){}
	
	inline unsigned int BufferId() const {return m_bufferId;}
	inline ruInt Size() const {return m_size;}
	inline rGeometryType GeometryType() const {return m_geometryType;}
	
private:
	
	unsigned int m_bufferId;
	ruInt m_size;
	rGeometryType m_geometryType;
};

class RECONDITE_API rGeometry {
public:
	rGeometry (const rString& name, rGeometryProfile profile, unsigned int vertexBufferId, unsigned int vertexBoneLinkBufferId);
	
public:
	unsigned int VertexBufferId() const;
	unsigned int VertexBoneLinkBufferId() const;
	
	ruInt ElementBufferCount() const;
	rElementBuffer* GetElementBuffer(const rString& name) const;
	void GetElementBufferNames(rArrayString& names) const;
	rElementBuffer* AddElementBuffer(const rString& name, unsigned int bufferId, size_t elementCount, rGeometryType geometryType);

	const rVertexBoneLinkMap& GetVertexBoneLinks() const;
	void SetVertexBoneLinks(const rVertexBoneLinkMap& links);

	rGeometryProfile GeometryProfile() const;
	rString Name() const;

private:
    
    typedef std::map<rString, rElementBuffer*> rElementBufferIdMap;
    
private:

	unsigned int m_vertexBufferId; 
	unsigned int m_vertexBoneLinkBufferId;

	rElementBufferIdMap m_elementBufferIds;
	rVertexBoneLinkMap m_vertexBoneLinks;

	rGeometryProfile m_geometryProfile;
	rString m_name;
};

typedef std::map<rString, rGeometry*> rGeometryMap;

#endif
