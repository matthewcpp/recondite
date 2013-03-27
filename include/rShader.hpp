#ifndef R_SHADER_HPP
#define R_SHADER_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAsset.hpp"

class rShader : public rAsset{
public:
	rShader(unsigned int programId, int assetId, const rString& name, const rString& path);
	
	unsigned int ProgramId() const;
	
	virtual rAssetType Type() const;
	
private:
	unsigned int m_programId;
};

typedef std::map<rString, rShader*> rShaderMap;
typedef rShaderMap::iterator rShaderItr;
typedef rShaderMap::const_iterator rShaderConstItr;
typedef std::pair<rString, rShader*> rShadermapEntry;

#endif
