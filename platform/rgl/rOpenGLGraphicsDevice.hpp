#ifndef R_OPENGLGRAPHICSDEVICE_HPP
#define R_OPENGLGRAPHICSDEVICE_HPP

#include <istream>
#include <sstream>

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#ifdef __APPLE__
	#include <GL/glew.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#elif WIN32 || LINUX
	#include <GL/glew.h>
	#include <GL/gl.h>
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

#include "data/rImmediateBuffer.hpp"

class rOpenGLGraphicsDevice : public rGraphicsDevice{
public:
	rOpenGLGraphicsDevice();
	
	virtual bool Init();
	virtual bool IsInit() const;
	virtual void Uninit();
	
	virtual void SetClearColor(const rColor& color);
	virtual void SetClearColor(float r, float g, float b, float a);
	virtual void Clear();
	
	virtual void EnableDepthTesting(bool enable);

	virtual unsigned int CreateTexture(int width, int height, int bpp , const unsigned char* data);
	virtual void UnregisterTexture(int textureID);
	
	virtual unsigned int CreateShaderProgram(const rString& vertex, const rString& fragment);
	virtual void DeleteShaderProgram(unsigned int shaderId);
	
	virtual unsigned int CreateArrayBuffer(const char* data, size_t dataSize);
	virtual unsigned int CreateElementBuffer(const unsigned short* elementData, size_t elementDataSize);
	virtual void DeleteBuffer(unsigned int bufferId);

	virtual void SetViewport(int x , int y, int width, int height) ;
	virtual void SetActiveMaterial(rMaterial* material);

	virtual void RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBuffer, rMaterial* material);
	virtual void RenderImmediate(rImmediateBuffer& geometry, const rMatrix4& transform, rMaterial* material);
protected:
	
	GLuint CompileShader(GLenum type, const char* program);
	unsigned char* ReflectTexture(int width, int height, int bpp , const unsigned char* data);
	
	GLenum GLGeometryType(rGeometryType type) const;

	bool m_isInit;
	rString m_lastError;
};

#endif
