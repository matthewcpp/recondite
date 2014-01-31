#ifndef RI_GEOMETRY_HPP
#define RI_GEOMETRY_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

class rElementBuffer{
public:
	rElementBuffer() : bufferId(0), size(0), geometryType(rGEOMETRY_TRIANGLES) {}
	rElementBuffer(unsigned int buffer, size_t sz, rGeometryType t) : bufferId(buffer), size(sz), geometryType(t){}
	
	unsigned int BufferId() const {return bufferId;}
	size_t Size() const {return size;}
	rGeometryType GeometryType() const {return geometryType;}

	unsigned int* ElementData() const {return 0;}
	
private:
	
	unsigned int bufferId;
	size_t size;
	rGeometryType geometryType;
};

typedef std::map<rString, rElementBuffer> rElementBufferIdMap;

struct rGeometryAttribute{
	size_t offset;
	size_t size;
	size_t stride;
	rDataType type;
	rString name;
};

class riGeometry{
public:
	virtual unsigned int VertexBufferId() const = 0;

	virtual rElementBuffer* GetElementBuffer(const rString& name) const = 0;
	virtual bool HasElementBuffer(const rString& name) const = 0;

	virtual size_t AttributeCount() const = 0;
	virtual rGeometryAttribute* Attribute(size_t index) const = 0;

};

#endif