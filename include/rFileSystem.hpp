#ifndef R_FILESYSTEM_HPP
#define R_FILESYSTEM_HPP

#include <memory>

#include "rBuild.hpp"
#include "rString.hpp"

#include "stream/rIFileStream.hpp"
#include "stream/rOFileStream.hpp"

class RECONDITE_API riFileSystem {
public:
	virtual rIStream* OpenReadFileRef(const rString& path) = 0;
	virtual void CloseReadFileRef(rIStream* stream) = 0;
};

class RECONDITE_API rFileSystem : public riFileSystem {

public:
	typedef std::shared_ptr<rIStream> rIFileStreamHandle;
	typedef std::shared_ptr<rOStream> rOFileStreamHandle;

	rIFileStreamHandle GetReadFileRef(const rString& path);

	/**
	Opens a readable stream to a file.
	\param path path to the file to be opened
	\returns pointer to a file if one was able to be opened using the supplied path, otherwise nullptr.
	*/
	virtual rIStream* OpenReadFileRef(const rString& path) override;
	virtual void CloseReadFileRef(rIStream* stream) override;

	rOFileStreamHandle GetWriteFileRef(const rString& path);
};

#endif