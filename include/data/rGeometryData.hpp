#ifndef R_GEOMETRYDATA_HPP
#define R_GEOMETRYDATA_HPP

#include <map>
#include <fstream>
#include <cstring>
#include <utility>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rVector2.hpp"
#include "rVector3.hpp"
#include "rMatrix4.hpp"

#include "rVertexBoneLink.hpp"

struct rModelVertex{
	rModelVertex() {}
	rModelVertex(const rVector3& v, const rVector3& n, const rVector2& tc)
		:position(v), texCoord(tc), normal(n) {}

	rVector3 position;
	rVector2 texCoord;
	rVector3 normal;
};

typedef std::vector<rModelVertex> rModelVertexArray;

class rElementBufferData{
public:
	rElementBufferData();
	rElementBufferData(unsigned short* elements, size_t elementCount, rGeometryType type);
	
public:
	
	void SetElementData(unsigned short* elements, size_t elementCount, rGeometryType type);
	void Allocate(size_t count);
	
	const unsigned short* GetElementData() const;
	size_t ElementDataSize() const;
	size_t ElementCount() const;
	
	void Push(unsigned short v1, unsigned short v2, unsigned short v3);
	
	void Clear();
	
	rGeometryType GeometryType() const;
	void SetGeometryType(rGeometryType type);

private:
	
	rIndexArray m_elementData;
	rGeometryType m_geometryType;
};

typedef std::map<rString, rElementBufferData*> rElementBufferDataMap;

class rGeometryData{
public:
	rGeometryData();
	~rGeometryData();

	void Clear();
	
public:
	void Allocate(size_t size);

	size_t VertexCount() const;
	const char* VertexData() const;
	char* VertexData();
	size_t VertexDataSize() const;

	void SetVertex(size_t index, const rVector3& v, const rVector3& n, const rVector2& tc);
	void PushVertex(const rVector3& v, const rVector3& n, const rVector2& tc);
	bool GetVertex(size_t index, rModelVertex& data) const;
	
	void TransformVertex(size_t index, const rMatrix4& transform);

public:
	
	rElementBufferData* CreateElementBuffer(const rString& name);
	rElementBufferData* CreateElementBuffer(const rString& name, unsigned short* elements, size_t elementCount, rGeometryType type);
	
	size_t ElementBufferCount() const;
	bool RemoveElementBuffer(const rString& name);
	rElementBufferData* GetElementBuffer(const rString& name) const;
	void GetElementBufferNames(rArrayString& names) const;
	
public:

	const rVertexBoneLinkMap& VertexBoneLinks() const;
	size_t VertexBoneLinkCount() const;
	void CreateVertexBoneLink(unsigned short vertexIndex, unsigned short boneIndex, float weight);
	void CreateVetexBoneDataArray(rVertexBoneDataArray& vertexBoneData) const;
	
public:

	rString Path() const;
	void SetPath(const rString& path);

private:

	rModelVertexArray m_vertexData;
	rElementBufferDataMap m_elementBuffers;
	
	rString m_path;

	rVertexBoneLinkMap m_vertexBoneLinks;
};

#endif
