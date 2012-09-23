#ifndef R_MODELDATA_ENCODER_HPP
#define R_MODELDATA_ENCODER_HPP

#include <ostream>
#include <iostream>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rModelData.hpp"

class rModelDataEncoder{
public:
	
	int Encode(rModelData* modelData, std::ostream* stream);
	
private:
	int InitEncoder(rModelData* modelData, std::ostream* stream);
	int EncodeHeader();
	
	void EncodeString(const rString& str);
	
	int EncodeMaterials();
	int EncodeMaterial(rMaterialData* material);
	
	int EncodeMeshes();
	int EncodeMesh(rMeshData* mesh);
	
	int EncodeTextures();
	int EncodeTexture(rTextureData* texture);
	
private:
	int m_error;
	
	rModelData* m_modelData;
	std::ostream* m_stream;
};

#endif
