#include "BuildImport.hpp"

#include "stream/rIFileStream.hpp"
#include "asset/rModelData.hpp"

namespace recondite { namespace import {
	class RECONDITE_IMPORT_API ModelImporter{
	public:
		ModelImporter();
		~ModelImporter();

	public:
		int ImportModel(const rString& path, ModelData& modelData);

	private:
		struct Impl;
		Impl* _impl;
	};

}}