#ifndef R_ASSETMANIFESTDATAFILE_HPP
#define R_ASSETMANIFESTDATAFILE_HPP

#include <fstream>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "xml/rXMLDocument.hpp"
#include "xml/rXMLElement.hpp"

#include "data/rAssetManifestData.hpp"

class rAssetManifestDataReader{
public:

	rContentError ReadFromFile(const rString& path, rAssetManifestData& assetManifest);
	rContentError ReadFromStream(std::istream& stream, rAssetManifestData& assetManifest);

	rContentError ReadAssets(std::istream& stream, rAssetManifestData& assetManifest);
private:

};

class rAssetManifestDataWriter{
public:
	rContentError WriteToFile(const rString& path, const rAssetManifestData& assetManifest);
	rContentError WriteToStream(std::ostream& stream, const rAssetManifestData& assetManifest);

private:
	rContentError WriteAssets(std::ostream& stream, const rAssetManifestData& assetManifest);
};

#endif