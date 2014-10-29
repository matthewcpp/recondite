#include "data/rAssetManifestDataFile.hpp"

rContentError rAssetManifestDataReader::ReadFromFile(const rString& path, rAssetManifestData& assetManifest){
	rIFileStream file(path.c_str());
	rContentError error = rCONTENT_ERROR_NONE;

	if (!file){
		error = rCONTENT_ERROR_FILE_NOT_FOUND;
	}
	else{
		error = ReadFromStream(file, assetManifest);
	}

	assetManifest.SetPath(path);
	return error;
}

rContentError rAssetManifestDataReader::ReadFromStream(rIStream& stream, rAssetManifestData& assetManifest){
	assetManifest.Clear();
	rContentError error = rCONTENT_ERROR_NONE;

	if (stream){
		error = ReadAssets(stream, assetManifest);
	}
	else{
		error = rCONTENT_ERROR_STREAM_ERROR;
	}

	return error;

}

rContentError rAssetManifestDataReader::ReadAssets(rIStream& stream, rAssetManifestData& assetManifest){
	rXMLDocument document;
	int error = document.LoadFromStream(stream);

	if (!error){
		int type;
		rString name, path;

		rXMLElement* root = document.GetRoot();

		for (size_t i =0; i < root->NumChildren(); i++){
			rXMLElement* asset = root->GetChild(i);

			asset->GetChild(0)->GetText<int>(type);
			name = asset->GetChild(1)->Text();
			path = asset->GetChild(2)->Text();

			assetManifest.AddManifestEntry((rAssetType)type, name, path);
		}
		
		return rCONTENT_ERROR_NONE;
	}
	else{
		return rCONTENT_ERROR_PARSE_ERROR;
	}
}

//-------------------------------------------

rContentError rAssetManifestDataWriter::WriteToFile(const rString& path, const rAssetManifestData& assetManifest){
	std::ofstream file(path.c_str());
	rContentError error = rCONTENT_ERROR_NONE;

	if (!file){
		error = rCONTENT_ERROR_FILE_NOT_FOUND;
	}
	else{
		error = WriteToStream(file, assetManifest);
	}

	return error;
}

rContentError rAssetManifestDataWriter::WriteToStream(std::ostream& stream, const rAssetManifestData& assetManifest){
	rContentError error = rCONTENT_ERROR_NONE;

	if (stream){
		error = WriteAssets(stream, assetManifest);
	}
	else{
		error = rCONTENT_ERROR_STREAM_ERROR;
	}

	return error;
}

rContentError rAssetManifestDataWriter::WriteAssets(std::ostream& stream, const rAssetManifestData& assetManifest){
	rXMLDocument document;
	rXMLElement* root = document.CreateRoot("assets");

	for (size_t i = 0; i < assetManifest.AssetCount(); i++){
		rAssetManifestEntry* assetData = assetManifest.GetManifestEntry(i);
		rXMLElement* asset = root->CreateChild("asset");

		asset->CreateChild<rAssetType>("type", assetData->type);
		asset->CreateChild<rString>("name", assetData->name);
		asset->CreateChild<rString>("path", assetData->path);
	}

	int error=  document.WriteToStream(stream);

	if (error)
		return rCONTENT_ERROR_STREAM_ERROR;
	else
		return rCONTENT_ERROR_NONE;
}