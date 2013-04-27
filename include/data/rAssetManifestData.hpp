#ifndef R_ASSET_MANIFEST_DATA_HPP
#define R_ASSET_MANIFEST_DATA_HPP

#include <fstream>
#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "xml/rXMLDocument.hpp"
#include "xml/rXMLElement.hpp"

struct rAssetManifestEntry {
	rAssetType type;
	rString name;
	rString path;
};

typedef std::map<rString, rAssetManifestEntry> rAssetManifestEntryMap;
typedef rAssetManifestEntryMap::iterator rAssetManifestEntryItr;
typedef rAssetManifestEntryMap::const_iterator rAssetManifestEntryConstItr;

class rAssetManifestData {
public:
	rAssetManifestData(const rString& path);
	rAssetManifestData(std::istream& stream);
	
	rContentError LoadFromFile(const rString& path);
	rContentError LoadFromStream(std::istream& stream);
	
	rContentError WriteToFile(const rString& path);
	rContentError WriteToStream(std::ostream& stream);
	
	rContentError AddManifestEntry(rAssetType type, const rString& name, const rString& path);
	rContentError DeleteManifestEntry(rAssetType type, const rString& name);
	

	rContentError GetError() const;
	rString GetPath() const;
	size_t AssetCount(rAssetType type);
	
	void Clear();
	
private:
	void CreateAssetCategoryXML(const rString& name, const rAssetManifestEntryMap& category, rXMLElement* parent);
	rContentError ReadAssetCategory(rAssetType type, rXMLElement* parent);
	
private:
	
	rAssetManifestEntryMap m_manifestEntries[rASSET_NUM_TYPES];
	rContentError m_error;
	rString m_path;
};

#endif
