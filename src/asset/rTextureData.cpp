#include "asset/rTextureData.hpp"

#include <vector>
#include <cstdint>

struct rTextureFileHeader;

struct rTextureData::Impl
{
	std::vector<uint8_t> data;
	rSize size;
	int bpp;

	size_t GetPixelIndex(int x, int y) const;
	void InitHeader(rTextureFileHeader& header);
};

size_t rTextureData::Impl::GetPixelIndex(int x, int y) const{
	return (y * size.x * bpp) + (x * bpp);
}

rTextureData::rTextureData(){
	_impl.reset(new Impl());
	Clear();
}

rTextureData::~rTextureData(){}

void rTextureData::Clear(){
    _impl->bpp = 3;
	_impl->size.Set(0, 0);
	_impl->data.clear();
}

void rTextureData::Allocate(int width, int height, int bpp){
	Clear();

	_impl->size.Set(width, height);
	_impl->bpp = bpp;

	_impl->data.resize(width * height * bpp);
}

void rTextureData::Allocate(int width, int height, int bpp, const rColor& color){
	Allocate(width, height, bpp);
	FillColor(color);
}

void rTextureData::SetImageData(int width, int height, int bpp, const unsigned char* data){
	Allocate(width, height, bpp);
    
	memcpy(&_impl->data[0], data, _impl->data.size());
}

void rTextureData::SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	size_t index = _impl->GetPixelIndex(x, y);
	_impl->data[index] = r;
	_impl->data[index + 1] = g;
	_impl->data[index + 2] = b;
	
	if (_impl->bpp == 4)
		_impl->data[index + 3] = a;
}

void rTextureData::SetPixel(int x, int y, const rColor& color){
	size_t index = _impl->GetPixelIndex(x, y);
	_impl->data[index] = color.red;
	_impl->data[index + 1] = color.green;
	_impl->data[index + 2] = color.blue;

	if (_impl->bpp == 4)
		_impl->data[index + 3] = color.alpha;
}

void rTextureData::GetPixel(int x, int y, rColor& color) const{
	size_t index = _impl->GetPixelIndex(x, y);

	color.red = _impl->data[index];
	color.green = _impl->data[index + 1];
	color.blue = _impl->data[index + 2];
	
	if (_impl->bpp == 4)
		color.alpha = _impl->data[index + 3];
	else
		color.alpha = 255;
}

void rTextureData::FillColor(const rColor& color){
	for (int x = 0; x < _impl->size.x; x++){
		for (int y = 0; y < _impl->size.y; y++){
			SetPixel(x,y,color);
		}
	}
}

size_t rTextureData::DataSize() const{
	return _impl->data.size();
}

rSize rTextureData::TextureSize() const{
	return _impl->size;
}

int rTextureData::Width() const{
	return _impl->size.x;
}

int rTextureData::Height() const{
	return _impl->size.y;
}

int rTextureData::Bpp() const{
	return _impl->bpp;
}

unsigned char* rTextureData::Data() const{
	return _impl->data.data();
}

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

void rTextureData::Impl::InitHeader(rTextureFileHeader& header) {
	header.magicNumber = MagicNumber;
	header.version = CurrentVersion;
	header.width = size.x;
	header.height = size.y;
	header.bpp = bpp;
	header.compression = 0;
	header.unused1 = 0;
	header.unused2 = 0;
	header.unused3 = 0;
}

int rTextureData::Write(rOStream& stream) {

	if (stream.IsOk()) {
		rTextureFileHeader header;
		_impl->InitHeader(header);

		stream.Write((const char*)&header, sizeof(header));
		stream.Write((const char*)_impl->data.data(), _impl->data.size());

		return 0;
	}

	return 1;
}

int rTextureData::Read(rIStream& stream){
	if (stream.IsOk()) {
		rTextureFileHeader header;
		stream.Read((char*)&header, sizeof(rTextureFileHeader));

		size_t dataSize = header.bpp * header.width * header.height;

		Allocate(header.width, header.height, header.bpp);
		stream.Read((char*)_impl->data.data(), dataSize);

		return 0;
	}

	return 1;
}