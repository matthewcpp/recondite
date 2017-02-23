#include "rPath.hpp"

bool isSeperator(char c){
#ifdef WIN32
	return c == '/' || c == '\\';
#else
	return c == '/';
#endif
}

size_t findLastSeperator(const rString& str) {
	size_t count = str.size();

	if (count > 0) {
		count -= 1;

		for (size_t i = 0; i <= count; i++) {
			if (isSeperator(str[count - i])) {
				return count - i;
			}
		}
	}

	return rString::npos;
}

rString rPath::Directory(const rString& path){
	size_t pos = findLastSeperator(path);

	if (pos == rString::npos){
		return rString("");
	}
	else{
		return path.substr(0, pos);
	}
}

rString rPath::Filename(const rString& path){
	size_t namepos = findLastSeperator(path);
	size_t extpos = path.find_last_of('.');

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
	size_t pos = findLastSeperator(path);

	if (pos == rString::npos){
		return path;
	}
	else{
		return path.substr(pos + 1);
	}
}

rString rPath::Extension(const rString& path){
	size_t pos = path.find_last_of('.');

	if (pos == rString::npos){
		return rString("");
	}
	else{
		return path.substr(pos + 1);
	}
}

rString rPath::Combine(const rString& dir, const rString& filename){
	rString result = dir;

	if (dir.length() > 0 && filename.length() > 0){
		char dirLast = dir.last();
		char filenameFirst = filename.first();

		if (!isSeperator(dirLast) && !isSeperator(filenameFirst)){
			result += PathSeparator;
		}
	}

	result += filename;

	return result;
}

rString rPath::Assemble(const rString& dir, const rString& filename, const rString& ext){
	rString result = rPath::Combine(dir, filename);

	if (ext.length() > 0){
		char extFirst = ext.first();

		if (extFirst != '.')
			result += '.';

		result += ext;
	}

	return result;
}

void rPath::Split(const rString& path, rString* directory, rString* filename){
	if (directory)
		*directory = rPath::Directory(path);
		
	if (filename)
		*filename = rPath::FullFilename(path);
}

void rPath::Split(const rString& path, rString* directory, rString* filename, rString* ext){
	if (directory)
		*directory = rPath::Directory(path);
		
	if (filename)
		*filename = rPath::Filename(path);
		
	if (ext)
		*ext = rPath::Extension(path);
}

rString rPath::PopComponent(const rString& path) {
	size_t pos = findLastSeperator(path);

	if (pos != rString::npos) {
		if (pos == path.size() - 1) {
			for (size_t i = pos - 1; pos >= 0; i--) {
				if (isSeperator(path[i])) {
					return path.substr(0, i);
				}
			}
		}
		else {
			return path.substr(0, pos);
		}
	}


	return "";
}