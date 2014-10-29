#include "data/rTexture2DData.hpp"

const int rTexture2DData::magicNumber = 2019914866;

rTexture2DData::rTexture2DData(){
    Clear();
}

rTexture2DData::rTexture2DData(const rString& path){
    LoadFromPath(path);
}

rTexture2DData::rTexture2DData(rIStream& stream){
    LoadFromStream(stream);
}

rTexture2DData::rTexture2DData(int width, int height, int bpp, unsigned char* data){
    SetImageData(width, height, bpp, data);
}

rTexture2DData::~rTexture2DData(){
    Clear();
}

void rTexture2DData::Clear(){
    m_error = rCONTENT_ERROR_NONE;
    m_compressionType = rTexture2DCompressionNone;
    m_bpp = 0;
    m_size.Set(0,0);
    
    m_data.clear();
    m_path.clear();
}

rContentError rTexture2DData::LoadFromPath(const rString& path){
    Clear();
    
	rIFileStream stream(path);
    
    if (!stream)
	m_error = rCONTENT_ERROR_FILE_NOT_FOUND;
    else
	m_error = LoadFromStream(stream);

    SetPath(path);
    
    stream.Close();
    
    return m_error;
}

rContentError rTexture2DData::LoadFromStream(rIStream& stream){
    Clear();
    
    if (stream){
		m_error = ReadFileHeader(stream);
		m_error = ReadNonCompressedData(stream);
    }
    else
    	m_error = rCONTENT_ERROR_FILE_NOT_READABLE;
    
    return m_error;
}

rContentError rTexture2DData::ReadFileHeader(rIStream& stream){
    int magic;
    
    stream.Read((char*)&magic, 4);
    stream.Read((char*)&m_size, 8);
    stream.Read((char*)&m_bpp, 4);
    stream.Read((char*)&m_compressionType, 4);
    
    return rCONTENT_ERROR_NONE;
}

rContentError rTexture2DData::ReadNonCompressedData(rIStream& stream){
    int dataSize = m_size.x * m_size.y * m_bpp;
    m_data.resize(dataSize);
    
    stream.Read((char*)&m_data[0], dataSize);
    
    return rCONTENT_ERROR_NONE;
}


rContentError rTexture2DData::WriteToPath(const rString& path) const{
	rContentError error = rCONTENT_ERROR_NONE;
    std::ofstream stream(path.c_str(), std::ios::binary);
    
    if (!stream)
		error = rCONTENT_ERROR_FILE_NOT_WRITABLE;
    else
		error =  WriteToStream(stream);
    
    stream.close();
    
    return error;
}

rContentError rTexture2DData::WriteToStream(std::ostream& stream) const{
    
    WriteFileHeader(stream);
    WriteNonCompressedData(stream);
    
    return rCONTENT_ERROR_NONE;
}

rContentError rTexture2DData::WriteFileHeader(std::ostream& stream) const{
    
    stream.write((char*)&magicNumber, 4);
    stream.write((char*)&m_size, 8);
    stream.write((char*)&m_bpp, 4);
    stream.write((char*)&m_compressionType, 4);
    
    return rCONTENT_ERROR_NONE;
}

rContentError rTexture2DData::WriteNonCompressedData(std::ostream& stream) const{
    stream.write((char*)&m_data[0], m_data.size());
    
    return rCONTENT_ERROR_NONE;
}

rContentError rTexture2DData::SetImageData(int width, int height, int bpp, const unsigned char* data){
    Clear();
    
    m_size.x = width;
    m_size.y = height;
    m_bpp = bpp;
    
    int imgDataSize = width * height * bpp;
    m_data.resize(imgDataSize);
    
    memcpy(&m_data[0], data, imgDataSize);
    
    return rCONTENT_ERROR_NONE;
}

size_t rTexture2DData::GetPixelIndex(int x, int y) const{
	return (y * m_size.x * m_bpp) + (x * m_bpp);
}

void rTexture2DData::Allocate(int width, int height, int bpp,  bool initDefault){
	Clear();
	
	m_size.Set(width, height);
	m_bpp = bpp;
	
	size_t dataSize = width * height * bpp;
	m_data.resize(dataSize);
	
	if (initDefault){
	
		memset(&m_data[0] , 100, dataSize);
		
		if (bpp == 4){
			for (int h = 0; h < m_size.y; h++){
				for (int w = 0; w < m_size.x; w++){
					size_t index = GetPixelIndex(w, h);
					m_data[index + 3] = 255;
				}
			}
		}
	}
}

void rTexture2DData::SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	size_t index = GetPixelIndex(x, y);
	m_data[index] = r;
	m_data[index + 1] = g;
	m_data[index + 2] = b;
	
	if (m_bpp == 4)
		m_data[index + 3] = a;
}

void rTexture2DData::GetPixel(int x, int y, rColor& color) const{
	size_t index = GetPixelIndex(x, y);

	color.red = m_data[index];
	color.green = m_data[index + 1];
	color.blue = m_data[index + 2];
	
	if (m_bpp == 4)
		color.alpha = m_data[index + 3];
	else
		color.alpha = 255;
}

void rTexture2DData::FillColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	rColor c(r,g,b,a);
	FillColor(c);
}

void rTexture2DData::FillColor(const rColor& color){
	for (int x= 0; x < m_size.x; x++){
		for (int y = 0; y < m_size.y; y++){
			SetPixel(x,y,color);
		}
	}
}

void rTexture2DData::SetPixel(int x, int y, const rColor& color){
	SetPixel(x, y, color.red, color.green, color.blue, color.alpha);
}

rContentError rTexture2DData::SetData(int width, int height, int bpp, unsigned char* data){
	Allocate(width, height, bpp, false);
	size_t dataSize = GetDataSize();
	
	memcpy(&m_data[0] , data, dataSize);

	return rCONTENT_ERROR_NONE;
}

rTexture2DCompressionType rTexture2DData::GetCompressionType() const{
    return m_compressionType;
}

void rTexture2DData::SetCompressionType(rTexture2DCompressionType type){
    m_compressionType = type;
}

size_t rTexture2DData::GetDataSize() const{
    return m_data.size();
}

rContentError rTexture2DData::GetError() const{
    return m_error;
}

rSize rTexture2DData::GetTextureSize() const{
    return m_size;
}

int rTexture2DData::GetWidth() const{
    return m_size.x;
}

int rTexture2DData::GetHeight() const{
    return m_size.y; 
}

int rTexture2DData::GetBPP() const{
    return m_bpp;
}

const unsigned char* rTexture2DData::GetData() const{
    return &m_data[0];
}

rString rTexture2DData::GetPath() const{
	return m_path;
}

void rTexture2DData::SetPath(const rString& path){
	m_path = path;
}
