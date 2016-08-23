#ifndef R_IMAGEIMPORTER_HPP
#define R_IMAGEIMPORTER_HPP

#include "asset/rTextureData.hpp"

#include "BuildImport.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

namespace recondite { namespace import {
	class RECONDITE_IMPORT_API ImageImporter {
	public:
		ImageImporter() {}
		int ImportImage(const rString& path, rTextureData& data);
		int ImportImage(const char* imageBytes, size_t imageByteCount, rTextureData& data);

	rNO_COPY_CLASS(ImageImporter)
	};
}}

#endif