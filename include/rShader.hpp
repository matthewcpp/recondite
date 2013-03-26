#ifndef R_SHADER_HPP
#define R_SHADER_HPP

#include "rTypes.hpp"
#include "rAsset.hpp"

class rShader : public rAsset{
public:
	rShader(unsigned int programId, int assetId, const rString& name, const rString& path);
	
	unsigned int ProgramId() const;
	
	virtual rAssetType Type() const;
	
private:
	unsigned int m_programId;
};

#endif
