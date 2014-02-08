#ifndef R_PATH_HPP
#define R_PATH_HPP

#include "rTypes.hpp"

namespace rPath{
	rString Directory(const rString& path);
	rString Filename(const rString& path);
	rString FullFilename(const rString& path);
	rString Extension(const rString& path);

	rString Combine(const rString& dir, const rString& filename);
	rString Assemble(const rString& dir, const rString& filename, const rString& ext);
	
	void Split(const rString& path, rString* directory, rString* filename);
	void Split(const rString& path, rString* directory, rString* filename, rString* ext);
};

#endif
