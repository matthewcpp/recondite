#ifndef R_IMAGEIMPORTER_HPP
#define R_IMAGEIMPORTER_HPP

#include "asset/rTextureData.hpp"

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

namespace recondite { namespace import {
	class RECONDITE_API ImageImporter {
	public:
		ImageImporter() {}
		int ImportImage(const rString& path, rTextureData& data);

	rNO_COPY_CLASS(ImageImporter)
	};
}}

#endif