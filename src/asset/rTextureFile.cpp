#include "asset/rTextureFile.hpp"

const uint32_t MagicNumber = 2019914866; //rtex
const uint32_t CurrentVersion = 1;

struct rTextureFileHeader {
	uint32_t magicNumber;
	uint32_t version;
	uint32_t width;
	uint32_t height;
	uint32_t bpp;
	uint32_t compression;
	uint32_t unused1;
	uint32_t unused2;
	uint32_t unused3;
};

rContentError rTextureFile::Read(rFileSystem* fileSystem, const rString& path, rTextureData& textureData){
	auto file = fileSystem->GetReadFileRef(path);

	if (file) {
		rTextureFileHeader header;
		file->Read((char*)&header, sizeof(rTextureFileHeader));

		size_t dataSize = header.bpp * header.width * header.height;

		rCharArray charBuffer;
		charBuffer.resize(dataSize);
		file->Read(charBuffer.data(), dataSize);

		return rContentError::None;
	}

	return rContentError::Error;
}

void InitHeader(rTextureFileHeader& header, const rTextureData& textureData) {
	header.magicNumber = MagicNumber;
	header.version = CurrentVersion;
	header.width = textureData.Width();
	header.height = textureData.Height();
	header.bpp = textureData.Bpp();
	header.compression = 0;
	header.unused1 = 0;
	header.unused2 = 0;
	header.unused3 = 0;
}

rContentError rTextureFile::Write(rFileSystem* fileSystem, const rString& path, const rTextureData& textureData) {
	auto file = fileSystem->GetWriteFileRef(path);

	if (file) {
		rTextureFileHeader header;
		InitHeader(header, textureData);

		file->Write((const char*)&header, sizeof(header));
		file->Write((const char*)textureData.Data(), textureData.DataSize());

		return rContentError::None;
	}

	return rContentError::Error;
}