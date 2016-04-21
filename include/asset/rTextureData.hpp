#ifndef R_TEXTURE2DDATA_HPP
#define R_TEXTURE2DDATA_HPP

#include <memory>

#include "rBuild.hpp"
#include "rSize.hpp"
#include "rColor.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

class RECONDITE_API rTextureData {
public:
    rTextureData();
	~rTextureData();

	void Allocate(int width, int height, int bpp);
	void Allocate(int width, int height, int bpp, const rColor& color);

	void SetImageData(int width, int height, int bpp, const unsigned char* data);
	void SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	void SetPixel(int x, int y, const rColor& color);
	void GetPixel(int x, int y, rColor& color) const;

	void FillColor(const rColor& color);

	int Width() const;
	int Height() const;
	int Bpp() const;
	rSize TextureSize() const;

	const unsigned char* Data() const;
	size_t DataSize() const;

	void Clear();

	int Read(rIStream& stream);
	int Write(rOStream& stream);
    
private:

	struct Impl;
	std::unique_ptr<Impl> _impl;
};

#endif