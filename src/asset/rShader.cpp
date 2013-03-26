#include "rShader.hpp"

rShader::rShader(unsigned int programId, int assetId, const rString& name, const rString& path)
	:rAsset(assetId, name, path);
{
	m_programId = programId;
}

unsigned int rShader::ProgramId() const{
	return m_programId;
}

virtual rShader::rAssetType Type() const{
	return rASSET_SHADER;
}
