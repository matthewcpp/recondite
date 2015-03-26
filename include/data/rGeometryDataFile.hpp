#ifndef R_GEOMETRYDATAFILE_HPP
#define R_GEOMETRYDATAFILE_HPP

#include <fstream>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"
#include "rTypes.hpp"

#include "data/rModelGeometryData.hpp"

#define rGEOMETRY_MAGIC_NUMBER 1868916594 //rego

struct rGeometryFileHeader{
	int magicNumber;
	int version;
	ruInt vertexCount;
	ruInt elementBufferCount;
	ruInt vertexBoneLinkCount;
};

class RECONDITE_API rGeometryDataReader{
public:
	rGeometryDataReader();

	rContentError GetError() const;

	rContentError ReadFromFile(const rString& path, rModelGeometryData& geometryData);
	rContentError ReadFromStream(std::istream& stream, rModelGeometryData& geometryData);

private:
	void ReadHeader(std::istream& stream);
	void ReadVertexData(std::istream& stream);
	void ReadElementBufferData(std::istream& stream);
	void ReadVertexBoneLinks(std::istream& stream);

private:
	rModelGeometryData* m_geometryData;
	rContentError m_error;

	rGeometryFileHeader m_header;
};

class RECONDITE_API rGeometryDataWriter{
public:
	rGeometryDataWriter();

	rContentError GetError() const;

	rContentError WriteToFile(const rString& path, const rModelGeometryData& geometryData);
	rContentError WriteToStream(std::ostream& stream, const rModelGeometryData& geometryData);

private:

	void WriteFileHeader(std::ostream& stream);
	void WriteVertexData(std::ostream& stream);
	void WriteElementBufferData(std::ostream& stream);
	void WriteVertexBoneLinks(std::ostream& stream);

private:

	const rModelGeometryData* m_geometryData;
	rContentError m_error;

	rGeometryFileHeader m_header;
};

#endif