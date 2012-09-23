#ifndef R_MODELDATA_DECODER_HPP
#define R_MODELDATA_DECODER_HPP

#include <istream>
#include <iostream>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rModelData.hpp"

class rModelDataDecoder{
public:
	
	int Decode(std::istream* stream, rModelData* modelData);
	
private:
	int InitDecoder(std::istream* stream, rModelData* modelData);
	
	int DecodeHeader();
	int DecodeMaterials();
	int DecodeMaterial();
	
	int DecodeMeshes();
	int DecodeMesh();
	
	void DecodeString(rString& str);
	
private:
	int m_error;
	rModelHeader m_header;
	std::istream* m_stream;
	rModelData* m_modelData;
};

#endif
