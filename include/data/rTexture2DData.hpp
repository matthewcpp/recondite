#ifndef R_TEXTURE2DDATA_HPP
#define R_TEXTURE2DDATA_HPP

#include <string.h>
#include <fstream>

#include "rTypes.hpp"
#include "rDefs.hpp"
#include "rSize.hpp"

enum rTexture2DCompressionType{
    rTexture2DCompressionNone = 0
};

class rTexture2DData {
public:
    
    rTexture2DData();
    rTexture2DData(const rString& path);
    rTexture2DData(std::istream& stream);
    rTexture2DData(int width, int height, int bpp, unsigned char* data);
    ~rTexture2DData();
    
public:
    
    rContentError LoadFromPath(const rString& path);
    rContentError LoadFromStream(std::istream& stream);
    
    rContentError WriteToPath(const rString& path);
    rContentError WriteToStream(std::ostream& stream);
    
    rContentError SetImageData(int width, int height, int bpp, const unsigned char* data);
    
    void Clear();
    
    rString GetPath() const;
    void SetPath(const rString& path);
    
public:
    rTexture2DCompressionType GetCompressionType() const;
    void SetCompressionType(rTexture2DCompressionType type);
    
    size_t GetDataSize() const;
    rContentError GetError() const;
    
    rSize GetTextureSize() const;
    int GetWidth() const;
    int GetHeight() const;
    
    int GetBPP() const;
    const unsigned char* GetData() const;
    
private:
    
    rContentError ReadFileHeader(std::istream& stream);
    rContentError ReadNonCompressedData(std::istream& stream);
    
    rContentError WriteFileHeader(std::ostream& stream);
    rContentError WriteNonCompressedData(std::ostream& stream);
    
private:
    
    static const int magicNumber;
    
    rTexture2DCompressionType m_compressionType;
    rUnsigedByteArray m_data;
    
    rContentError m_error;
    rSize m_size;
    int m_bpp;
    
    rString m_path;
};

#endif