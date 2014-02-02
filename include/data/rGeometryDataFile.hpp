#ifndef R_GEOMETRYDATAFILE_HPP
#define R_GEOMETRYDATAFILE_HPP

#include <fstream>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "data/rGeometryData.hpp"

struct rGeometryFileHeader{
	int magicNumber;
	int version;
	size_t vertexCount;
	size_t elementBufferCount;
	size_t vertexBoneLinkCount;
};

#define rGEOMETRY_MAGIC_NUMBER 1868916594 //rego

class rGeometryDataReader{
public:
	rGeometryDataReader();

	rContentError GetError() const;

	rContentError ReadFromFile(const rString& path, rGeometryData& geometryData);
	rContentError ReadFromStream(std::istream& stream, rGeometryData& geometryData);

private:
	void ReadHeader(std::istream& stream);
	void ReadVertexData(std::istream& stream);
	void ReadElementBufferData(std::istream& stream);
	void ReadVertexBoneLinks(std::istream& stream);

private:
	rGeometryData* m_geometryData;
	rContentError m_error;

	rGeometryFileHeader m_header;
};

class rGeometryDataWriter{
public:
	rGeometryDataWriter();

	rContentError GetError() const;

	rContentError WriteToFile(const rString& path, const rGeometryData& geometryData);
	rContentError WriteToStream(std::ostream& stream, const rGeometryData& geometryData);

private:

	void WriteFileHeader(std::ostream& stream);
	void WriteVertexData(std::ostream& stream);
	void WriteElementBufferData(std::ostream& stream);
	void WriteVertexBoneLinks(std::ostream& stream);

private:

	const rGeometryData* m_geometryData;
	rContentError m_error;

	rGeometryFileHeader m_header;
};

#endif