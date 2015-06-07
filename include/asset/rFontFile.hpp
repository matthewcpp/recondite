#ifndef R_FONTFILE_HPP
#define R_FONTFILE_HPP

#include <memory>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "rFileSystem.hpp"

#include "rFontData.hpp"

class RECONDITE_API rFontFile{
public:
	static rContentError Read(rFileSystem* fileSystem, const rString& path, std::unique_ptr<rFontData>& fontData);
};

#endif