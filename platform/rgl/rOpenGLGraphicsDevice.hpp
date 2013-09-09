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

#include "rLog.hpp"

#include "rAlignedBox3.hpp"

#include "rViewport.hpp"
#include "rMaterial.hpp"

#include "rGraphicsDevice.hpp"
#include "rMatrix4.hpp"

class rOpenGLGraphicsDevice : public rGraphicsDevice{
public:
	rOpenGLGraphicsDevice();
	
	virtual bool Init();
	virtual bool IsInit() const;
	virtual void Uninit();
	
	virtual void SetClearColor(const rColor& color);
	virtual void SetClearColor(float r, float g, float b, float a);
	virtual void Clear();
	
	virtual unsigned int CreateTexture(int width, int height, int bpp , const unsigned char* data);
	virtual void UnregisterTexture(int textureID);
	
	virtual unsigned int CreateShaderProgram(const rString& vertex, const rString& fragment);
	virtual void DeleteShaderProgram(unsigned int shaderId);
	
	virtual unsigned int CreateVertexBuffer(const float* vertexData, size_t vertexDataSize);
	virtual unsigned int CreateElementBuffer(const unsigned short* elementData, size_t elementDataSize);
	virtual void DeleteBuffer(unsigned int bufferId);

	virtual void SetViewport(int x , int y, int width, int height) ;
	virtual void SetActiveMaterial(rMaterial* material);
	
	virtual void RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBuffer, rMaterial* material);

	
protected:
	
	GLuint CompileShader(GLenum type, const char* program);
	
	GLsizei GetVertexStrideForGeometry(const rGeometry* geometry) const;
	
	bool m_isInit;
	rString m_lastError;
};

#endif