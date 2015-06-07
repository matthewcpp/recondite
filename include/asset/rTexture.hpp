#ifndef R_TEXTURE2D_HPP
#define R_TEXTURE2D_HPP

#include <map>
#include <vector>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

class RECONDITE_API rTexture{
public:
	
	rTexture(const rString& name, int width, int height, int bpp, unsigned int graphicsDeviceId);
	
	int Width() const;
	int Height() const;
	int GraphicsDeviceID() const;
	int Bpp() const;
	rString Name() const;
	
private:
	
	int m_width , m_height;
	int m_bpp;
	unsigned int m_graphicsDeviceId;
	rString m_name;
};

#endif