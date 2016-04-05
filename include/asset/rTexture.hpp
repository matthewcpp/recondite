#ifndef R_TEXTURE2D_HPP
#define R_TEXTURE2D_HPP

#include <map>
#include <vector>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"
#include "rSize.hpp"

class RECONDITE_API rTexture{
public:
	
	rTexture(const rString& name, int width, int height, int bpp, unsigned int graphicsDeviceId);
	
	int Width() const;
	int Height() const;
	rSize Size() const;
	int GraphicsDeviceID() const;
	int Bpp() const;
	rString Name() const;
	
private:
	
	rSize m_size;
	int m_bpp;
	unsigned int m_graphicsDeviceId;
	rString m_name;
};

#endif