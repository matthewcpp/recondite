#ifndef R_OPENGLGRAPHICSDEVICE_HPP
#define R_OPENGLGRAPHICSDEVICE_HPP

#include <istream>
#include <sstream>

#include <GL/glew.h>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif


#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rVector2.hpp"
#include "rRectangle2.hpp"
#include "rCircle2.hpp"
#include "rTriangle2.hpp"

#include "rVector3.hpp"
#include "rCone3.hpp"
#include "rAlignedBox3.hpp"
#include "rSphere3.hpp"
#include "rMatrix4.hpp"
#include "rViewport.hpp"

#include "rMaterial.hpp"
#include "rTexture2D.hpp"

#include "rGraphicsDevice.hpp"

#define rOGL_FOV_ANGLE 45.0f
#define rOGL_Z_NEAR 0.01f
#define rOGL_Z_FAR 10000.0f

class rOpenGLGraphicsDevice : public rGraphicsDevice{
public:
	rOpenGLGraphicsDevice();
	
	virtual bool Init();
	virtual bool IsInit() const;
        virtual bool HasCalledInit() const;
	virtual void Uninit();
	virtual void Clear();
	
	virtual unsigned int GenerateTextureID();
	virtual unsigned int CreateTexture(int width, int height, int bpp , const unsigned char* data);
	virtual void UnregisterTexture(int textureID);
	virtual void BindTexture2D(unsigned int textureID);

	virtual void SetActiveViewport(rViewport& viewport);
	virtual int Unproject(const rVector3& v, rVector3& world);

	virtual void DrawLines3(const rVertex3Array& lines , const rColor& color);
	virtual void DrawPoints3(const rVertex3Array& points , const rColor& color);

	virtual void DrawWireBox(const rAlignedBox3& b, const rColor& color);
	virtual void DrawMesh(rVertex3Array& verticies, rVector2Array& texCoords, rIndexArray& indicies, rMaterial* material);

	virtual unsigned int CreateShaderProgram(const rString& vertex, const rString& fragment);
	virtual void DeleteShaderProgram(unsigned int shaderId);
	
protected:
	
	GLuint CreateShader(GLenum type, const char* program);

	void DisableTextures();

	void Set2DView(rViewport& viewport);
	void SetPerspView(rViewport& viewport);
	void CameraLookAt(rCamera* camera);
	
	void SetActiveMaterial(rMaterial* material);
	
	unsigned int InitDefaultShader();

	bool m_isInit;
        bool m_calledInit;
	unsigned int m_defaultShader;
};

#endif