#ifndef R_OPENGLGRAPHICSDEVICE_HPP
#define R_OPENGLGRAPHICSDEVICE_HPP

#include <istream>
#include <sstream>

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#elif WIN32 || LINUX
	#include <GL/gl.h>
	#include <GL/glu.h>
#else
	#include <GLES2/gl2.h>
#endif


#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rAlignedBox3.hpp"

#include "rViewport.hpp"
#include "rMaterial.hpp"

#include "rGraphicsDevice.hpp"

class rOpenGLGraphicsDevice : public rGraphicsDevice{
public:
	rOpenGLGraphicsDevice();
	
	virtual bool Init();
	virtual bool IsInit() const;
	virtual void Uninit();
	virtual void Clear();
	
	virtual unsigned int CreateTexture(int width, int height, int bpp , const unsigned char* data);
	virtual void UnregisterTexture(int textureID);
	
	virtual unsigned int CreateShaderProgram(const rString& vertex, const rString& fragment);
	virtual void DeleteShaderProgram(unsigned int shaderId);

	virtual void SetActiveViewport(rViewport& viewport);
	void SetActiveMaterial(rMaterial* material);
	
	virtual void SetClearColor(const rColor& color);
	virtual void SetClearColor(float r, float g, float b, float a);

	virtual void DrawLines3(const rVertex3Array& lines , const rColor& color);
	virtual void DrawPoints3(const rVertex3Array& points , const rColor& color);
	virtual void DrawWireBox(const rAlignedBox3& b, const rColor& color);
	
protected:
	
	GLuint CompileShader(GLenum type, const char* program);

	bool m_isInit;
	rString m_lastError;
};

#endif