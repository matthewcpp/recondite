#include "asset/rTextureData.hpp"

rTextureData::rTextureData(){
	Clear();
}

void rTextureData::Clear(){
    m_bpp = 3;
    m_size.Set(0,0);
	m_data.clear();
}

void rTextureData::Allocate(int width, int height, int bpp){
	Clear();

	m_size.Set(width, height);
	m_bpp = bpp;

	int imgDataSize = width * height * bpp;
	m_data.resize(imgDataSize);
}

void rTextureData::Allocate(int width, int height, int bpp, const rColor& color){
	Allocate(width, height, bpp);
	FillColor(color);
}

void rTextureData::SetImageData(int width, int height, int bpp, const unsigned char* data){
	Allocate(width, height, bpp);
    
    memcpy(&m_data[0], data, m_data.size());
}

size_t rTextureData::GetPixelIndex(int x, int y) const{
	return (y * m_size.x * m_bpp) + (x * m_bpp);
}


void rTextureData::SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	size_t index = GetPixelIndex(x, y);
	m_data[index] = r;
	m_data[index + 1] = g;
	m_data[index + 2] = b;
	
	if (m_bpp == 4)
		m_data[index + 3] = a;
}

void rTextureData::SetPixel(int x, int y, const rColor& color){
	SetPixel(x, y, color.red, color.green, color.blue, color.alpha);
}

void rTextureData::GetPixel(int x, int y, rColor& color) const{
	size_t index = GetPixelIndex(x, y);

	color.red = m_data[index];
	color.green = m_data[index + 1];
	color.blue = m_data[index + 2];
	
	if (m_bpp == 4)
		color.alpha = m_data[index + 3];
	else
		color.alpha = 255;
}

void rTextureData::FillColor(const rColor& color){
	for (int x= 0; x < m_size.x; x++){
		for (int y = 0; y < m_size.y; y++){
			SetPixel(x,y,color);
		}
	}
}

size_t rTextureData::DataSize() const{
    return m_data.size();
}


rSize rTextureData::TextureSize() const{
    return m_size;
}

int rTextureData::Width() const{
    return m_size.x;
}

int rTextureData::Height() const{
    return m_size.y; 
}

int rTextureData::Bpp() const{
    return m_bpp;
}

const unsigned char* rTextureData::Data() const{
	return m_data.data();
}