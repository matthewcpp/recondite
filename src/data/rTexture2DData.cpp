#include "data/rTexture2DData.hpp"

const int rTexture2DData::magicNumber = 2019914866;

rTexture2DData::rTexture2DData(){
    Clear();
}

rTexture2DData::rTexture2DData(const rString& path){
    LoadFromPath(path);
}

rTexture2DData::rTexture2DData(std::istream& stream){
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
}

rContentError rTexture2DData::LoadFromPath(const rString& path){
    Clear();
    
    std::ifstream stream(path.c_str(), std::ios::binary);
    
    if (!stream)
	m_error = rCONTENT_ERROR_FILE_NOT_FOUND;
    else
	m_error = LoadFromStream(stream);
    
    stream.close();
    
    return m_error;
}

rContentError rTexture2DData::LoadFromStream(std::istream& stream){
    Clear();
    
    ReadFileHeader(stream);
    ReadNonCompressedData(stream);
    
    return m_error;
}

rContentError rTexture2DData::ReadFileHeader(std::istream& stream){
    int magic;
    
    stream.read((char*)&magic, 4);
    stream.read((char*)&m_size, 8);
    stream.read((char*)&m_bpp, 4);
    stream.read((char*)&m_compressionType, 4);
}

rContentError rTexture2DData::ReadNonCompressedData(std::istream& stream){
    int dataSize = m_size.x * m_size.y * m_bpp;
    m_data.resize(dataSize);
    
    stream.read((char*)&m_data[0], dataSize);
    
    return rCONTENT_ERROR_NONE;
}


rContentError rTexture2DData::WriteToPath(const rString& path){
    std::ofstream stream(path.c_str(), std::ios::binary);
    
    if (!stream)
	m_error = rCONTENT_ERROR_FILE_NOT_WRITABLE;
    else
	m_error =  WriteToStream(stream);
    
    stream.close();
    
    return m_error;
}

rContentError rTexture2DData::WriteToStream(std::ostream& stream){
    m_error = rCONTENT_ERROR_NONE;
    
    WriteFileHeader(stream);
    WriteNonCompressedData(stream);
    
    return m_error;
}

rContentError rTexture2DData::WriteFileHeader(std::ostream& stream){
    
    stream.write((char*)&magicNumber, 4);
    stream.write((char*)&m_size, 8);
    stream.write((char*)&m_bpp, 4);
    stream.write((char*)&m_compressionType, 4);
    
    return rCONTENT_ERROR_NONE;
}

rContentError rTexture2DData::WriteNonCompressedData(std::ostream& stream){
    stream.write((char*)&m_data[0], m_data.size());
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

unsigned char* rTexture2DData::GetData() const{
    return &m_data[0];
}