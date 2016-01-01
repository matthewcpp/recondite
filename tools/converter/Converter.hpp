#pragma once

#include <functional>
#include <map>

#include "rFileSystem.hpp"
#include "rPath.hpp"

#include "ImageImporter.hpp"
#include "asset/rTextureData.hpp"
#include "asset/rTextureFile.hpp"

#include "rString.hpp"

#include "3rdParty/LambdaOptions.h"

namespace recondite { namespace tools {
	class Converter {
	public:
		int Main(int argc, char** argv);

		int ConvertImage(const rString& path);

	private:
		rFileSystem m_fileSystem;
	};
}}

