#include "BuildImport.hpp"

#include "ImageImporter.hpp"

#include "stream/rIFileStream.hpp"
#include "asset/rModelData.hpp"

namespace recondite { namespace import {
	struct RECONDITE_IMPORT_API ModelImporterOptions {
		bool importMeshData;
		bool importSkeleton;
		bool importAnimations;

		ModelImporterOptions() :
			importMeshData(true),
			importSkeleton(true),
			importAnimations(true) {}
	};
	class RECONDITE_IMPORT_API ModelImporter{
	public:
		ModelImporter();
		~ModelImporter();

	public:
		int ImportModel(const rString& path, ModelData& modelData, const ModelImporterOptions& options);

	private:
		struct Impl;
		Impl* _impl;
	};

}}