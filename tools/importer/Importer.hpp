#pragma once

#include <functional>
#include <map>

#include "rString.hpp"
#include "rFileSystem.hpp"

#include "3rdParty/LambdaOptions.h"

namespace recondite { namespace tools {
	class Importer {
	public:
		int Main(int argc, char** argv);

		int ConvertImage(const rString& path);
		int CreateTextureAtlas(const rString& path);
		int ConvertFont(const rString& path);
		int ConvertModel(const rString& path);

	private:
		rFileSystem m_fileSystem;
	};
}}

