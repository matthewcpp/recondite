#ifndef R_TEXTURE2D_HPP
#define R_TEXTURE2D_HPP

#include <map>
#include <vector>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"
#include "rSize.hpp"
#include "rVector2.hpp"

class RECONDITE_API rTexture{
public:
	
	rTexture(const rString& name, int width, int height, int bpp, unsigned int graphicsDeviceId);
	rTexture(const rString& name, const rSize& size, int bpp, const rVector2& uvOrigin, const rVector2 uvSize, unsigned int graphicsDeviceId);
	
	int Width() const;
	int Height() const;
	rSize Size() const;
	int GraphicsDeviceID() const;
	int Bpp() const;
	rString Name() const;

	const rVector2& UVOrigin() const;
	const rVector2& UVSize() const;
	
private:
	
	rSize m_size;
	int m_bpp;
	unsigned int m_graphicsDeviceId;
	rString m_name;

	rVector2 m_uvOrigin;
	rVector2 m_uvSize;
};

#endif