#ifndef RI_GEOMETRY_HPP
#define RI_GEOMETRY_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"



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