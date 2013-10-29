#include "rPath.hpp"

rString rPath::Directory(const rString& path){
	size_t pos = path.find_last_of("/");

	if (pos == rString::npos){
		return rString("");
	}
	else{
		return path.substr(0, pos);
	}
}

rString rPath::Filename(const rString& path){
	size_t namepos = path.find_last_of("/");
	size_t extpos = path.find_last_of(".");

	if (namepos == rString::npos){
		namepos = 0;
	}
	else {
		namepos += 1;
	}

	if (extpos == rString::npos){
		return path.substr(namepos);
	}
	else{
		return path.substr(namepos, extpos - namepos);
	}
}

rString rPath::FullFilename(const rString& path){
	size_t pos = path.find_last_of("/");

	if (pos == rString::npos){
		return path;
	}
	else{
		return path.substr(pos + 1);
	}
}

rString rPath::Extension(const rString& path){
	size_t pos = path.find_last_of(".");

	if (pos == rString::npos){
		return rString("");
	}
	else{
		return path.substr(pos + 1);
	}
}

rString rPath::Combine(const rString& dir, const rString& filename){
	rString result = dir;

	char dirLast = *dir.rbegin();
	char filenameFirst = *filename.begin();

	if (dirLast != '/' && filenameFirst != '/'){
		result += '/';
	}

	result += filename;

	return result;
}

rString rPath::Assemble(const rString& dir, const rString& filename, const rString& ext){
	rString result = rPath::Combine(dir, filename);

	char extFirst = *ext.begin();

	if (extFirst != '.')
		result += '.';

	result += ext;

	return result;
}