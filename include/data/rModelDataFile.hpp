#ifndef R_MODELDATAFILE_HPP
#define R_MODELDATAFILE_HPP

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "data/rModelData.hpp"
#include "xml/rXMLDocument.hpp"

#include "stream/rIFileStream.hpp"

class RECONDITE_API rModelDataWriter {
public:
	rContentError WriteToFile(const rString& dir, const rModelData& modelData);

private:
	rContentError WriteDependencies(const rString& dir, const rModelData& modelData);
};

class RECONDITE_API rModelDataReader {
public:
	rContentError LoadFromFile(const rString& path, rModelData& modelData);
	rContentError LoadFromStream(rIStream& stream, rModelData& modelData);
};

#endif