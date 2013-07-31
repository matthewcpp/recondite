#ifndef R_GEOMETRY_HPP
#define R_GEOMETRY_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"

class rGeometry : public rAsset{
public:
	rGeometry (unsigned int vertexBufferId, unsigned int elementBufferId, bool texCoords, bool normals, 
		int assetid, const rString& name, const rString& path);
	
public:
	unsigned int VertexBufferId() const;
	unsigned int ElementBufferId() const;
	
	bool HasTexCoords() const;
	bool HasNormals() const;
	
	virtual rAssetType Type() const;
private:

	unsigned int m_vertexBufferId; 
	unsigned int m_elementBufferId; 
	bool m_hasTexCoords; 
	bool m_hasNormals;
	
};

typedef std::map<rString, rGeometry*> rGeometryMap;

#endif
