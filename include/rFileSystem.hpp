#ifndef R_FILESYSTEM_HPP
#define R_FILESYSTEM_HPP


#include "rBuild.hpp"
#include "rString.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

class RECONDITE_API riFileSystem {
public:
	/**
	Opens a readable stream to a file.
	\param path path to the file to be opened.
	\returns pointer to a file if one was able to be opened using the supplied path, otherwise nullptr.
	*/
	virtual rIStream* OpenReadFileRef(const rString& path) = 0;

	/**
	Closes readable stream opened with OpenReadFileRef.
	\param stream the stream to close.  After the call to this function, this pointer is no longer valid.
	*/
	virtual void CloseReadFileRef(rIStream* stream) = 0;

	/**
	Opens a writable stream to a file.
	\param path path to the file to be opened.
	\returns pointer to a file if one was able to be opened using the supplied path, otherwise nullptr.
	*/
	virtual rOStream* OpenWriteFileRef(const rString& path) = 0;

	/**
	Closes writable stream opened with OpenWriteFileRef.
	\param stream the stream to close.  After the call to this function, this pointer is no longer valid.
	*/
	virtual void CloseWriteFileRef(rOStream* stream) = 0;

	/**
	Returns whether a path exists
	\param path the path to query
	\returns value indicating if the path exists
	*/
	virtual bool Exists(const rString& path) = 0;

	/**
	Gets the file size for a path
	\param path the path to query
	\param size the size of the file at the given path if no error occurred.
	\returns value indicating if the call was successfull
	*/
	virtual bool FileSize(const rString& path, size_t& size) const = 0;
};

class RECONDITE_API rFileSystem : public riFileSystem {
public:
	virtual rIStream* OpenReadFileRef(const rString& path) override;
	virtual void CloseReadFileRef(rIStream* stream) override;

	virtual rOStream* OpenWriteFileRef(const rString& path);
	virtual void CloseWriteFileRef(rOStream* stream);

	virtual bool Exists(const rString& path);
	virtual bool FileSize(const rString& path, size_t& size) const;
};

#endif