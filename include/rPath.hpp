#ifndef R_PATH_HPP
#define R_PATH_HPP

#include "rBuild.hpp"
#include "rString.hpp"

namespace rPath{
	rString RECONDITE_API Directory(const rString& path);
	rString RECONDITE_API Filename(const rString& path);
	rString RECONDITE_API FullFilename(const rString& path);
	rString RECONDITE_API Extension(const rString& path);

	rString RECONDITE_API PopComponent(const rString& path);

	rString RECONDITE_API Combine(const rString& dir, const rString& filename);
	rString RECONDITE_API Assemble(const rString& dir, const rString& filename, const rString& ext);
	
	void RECONDITE_API Split(const rString& path, rString* directory, rString* filename);
	void RECONDITE_API Split(const rString& path, rString* directory, rString* filename, rString* ext);

	const char PathSeparator = '/';
};

#endif
