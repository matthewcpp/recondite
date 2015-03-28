#ifndef R_GEOMETRYDATA_HPP
#define R_GEOMETRYDATA_HPP

#include <map>
#include <fstream>
#include <cstring>
#include <utility>
#include <memory>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rTypes.hpp"
#include "rString.hpp"

#include "rVector2.hpp"
#include "rVector3.hpp"
#include "rMatrix4.hpp"

#include "rVertexBoneLink.hpp"

class RECONDITE_API rElementBufferData{
public:
	rElementBufferData(rGeometryType geometryType);
	rElementBufferData(unsigned short* elements, size_t elementCount, rGeometryType type);
	
public:
	
	void SetElementData(unsigned short* elements, size_t elementCount, rGeometryType type);
	void Allocate(size_t count);
	
	const unsigned short* GetElementData() const;
	size_t ElementDataSize() const;
	size_t ElementCount() const;
	
	void Push(unsigned short v1, unsigned short v2, unsigned short v3);
	void Push(unsigned short v1, unsigned short v2);
	
	void Clear();
	
	rGeometryType GeometryType() const;
	void SetGeometryType(rGeometryType type);

private:
	
	rIndexArray m_elementData;
	rGeometryType m_geometryType;
};

class RECONDITE_API rGeometryData{
public:
	rGeometryData(){}
	virtual void Clear();

	virtual void TransformVertex(size_t index, const rMatrix4& transform) = 0;
	virtual void PushVertex(const rVector3& position, const rVector3& normal) = 0;
	virtual void GetVertex(size_t index, rVector3* position, rVector3* normal) const = 0;

	virtual size_t VertexCount() const = 0;
	virtual char* VertexData() const = 0;
	virtual size_t VertexDataSize() const = 0;

public:

	size_t VertexBoneLinkCount() const;
	size_t CreateVertexBoneLink(unsigned short vertexIndex, unsigned short boneIndex, float weight);
	bool GetVertexBoneLink(size_t index, rVertexBoneLink& boneLink);
	
public:
	rElementBufferData* CreateElementBuffer(const rString& name, rGeometryType geometryType);
	
	size_t ElementBufferCount() const;
	void RemoveElementBuffer(const rString& name);
	rElementBufferData* GetElementBuffer(const rString& name) const;
	void GetElementBufferNames(rArrayString& names) const;

private:

	typedef std::shared_ptr<rElementBufferData> rElementBufferDataPtr;
	typedef std::map<rString, rElementBufferDataPtr> rElementBufferDataMap;
	typedef std::vector<rVertexBoneLink> rVertexBoneLinkVector;

private:

	rElementBufferDataMap m_elementBuffers;
	rVertexBoneLinkVector m_vertexBoneLinks;
	
	rString m_path;

	rNO_COPY_CLASS(rGeometryData)
};

#endif
