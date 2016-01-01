#ifndef R_IMAGEIMPORTER_HPP
#define R_IMAGEIMPORTER_HPP

#include "asset/rTextureData.hpp"

#include "rBuild.hpp"

namespace recondite { namespace import {
	class RECONDITE_API ImageImporter {
	public:
		int ImportImage(const rString& path, rTextureData& data);
	};
}}

#endif