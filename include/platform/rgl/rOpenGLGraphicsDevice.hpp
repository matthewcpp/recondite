#ifndef R_OPENGLGRAPHICSDEVICE_HPP
#define R_OPENGLGRAPHICSDEVICE_HPP

#include <istream>
#include <sstream>
#include <map>

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#ifdef __APPLE__
	#include <GL/glew.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#elif WIN32 || __linux__
	#include <GL/glew.h>
	#include <GL/gl.h>
#else
	#include <GLES2/gl2.h>
#endif

#include "rBuild.hpp"

#include "rTypes.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "rLog.hpp"

#include "rAlignedBox3.hpp"

#include "rViewport.hpp"
#include "asset/rMaterial.hpp"

#include "rGraphicsDevice.hpp"
#include "rMatrix4.hpp"

#include "data/rImmediateBuffer.hpp"

class RECONDITE_API rOpenGLGraphicsDevice : public rGraphicsDevice{
public:
	rOpenGLGraphicsDevice();
	
	virtual bool Init();
	virtual bool IsInit() const;
	virtual void Uninit();
	
	virtual void SetClearColor(const rColor& color);
	virtual void Clear();
	
	virtual void EnableDepthTesting(bool enable);
	virtual void EnablePolygonFillOffset(bool enable);

	virtual unsigned int CreateTexture(int width, int height, int bpp , const unsigned char* data);
	virtual void UnregisterTexture(int textureID);
	
	virtual unsigned int CreateShaderProgram(const rString& vertex, const rString& fragment);
	virtual void DeleteShaderProgram(unsigned int shaderId);
	virtual void ActivateShader(unsigned int shaderId);
	
	virtual unsigned int CreateArrayBuffer(const char* data, size_t dataSize);
	virtual unsigned int CreateElementBuffer(const unsigned short* elementData, size_t elementDataSize);
	virtual void DeleteBuffer(unsigned int bufferId);

	virtual void SetViewport(int x , int y, int width, int height) ;
	virtual void SetActiveMaterial(rMaterial* material);

	virtual void RenderGeometry(const rGeometry* geometry, const rMatrix4& projection, const rMatrix4& modelview, const rString& elementBuffer, rMaterial* material);
	virtual void RenderImmediate(const rImmediateBuffer& geometry, const rMatrix4& transform, rMaterial* material);

	virtual unsigned int CreateRenderbuffer(int width, int height);
	virtual void DeleteRenderbuffer(unsigned int id);
	virtual unsigned int ReadRenderbufferPixel(unsigned int x, unsigned int y);

protected:
	
	GLuint CompileShader(GLenum type, const char* program);
	unsigned char* ReflectTexture(int width, int height, int bpp , const unsigned char* data);
	
	GLenum GLGeometryType(rGeometryType type) const;

	bool m_isInit;
	rString m_lastError;

private:
	void RenderTexCoordGeometryProfile(const rGeometry* geometry, const rMatrix4& projection, const rMatrix4& modelview, rElementBuffer* elementBuffer, rMaterial* material);
	void RenderPrimitiveGeometryProfile(const rGeometry* geometry, const rMatrix4& projection, const rMatrix4& modelview, rElementBuffer* elementBuffer, rMaterial* material);
private:
	struct rglRenderbuffer{
		GLuint framebufferId;
		GLuint renderbufferId;
		GLuint depthBufferId;

		int width;
		int height;
	};

	typedef std::map<unsigned int, rglRenderbuffer> rglRenderbufferMap;

private:
	rglRenderbufferMap m_renderBuffers;
	GLint m_defaultFramebuffer;
	GLint m_activeShaderProgram;

	unsigned int m_nextRenderbufferId;
	unsigned int m_activeRenderBufferId;

	rColor m_clearColor;
};

#endif
