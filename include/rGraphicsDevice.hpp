#ifndef R_GRAPHICSDEVICE_HPP
#define R_GRAPHICSDEVICE_HPP

#include <cmath>
#include <vector>

#include "rBuild.hpp"
#include "rDefs.hpp"

#include "rViewport.hpp"
#include "rAlignedBox3.hpp"

#include "asset/rMaterial.hpp"
#include "asset/rGeometry.hpp"

#include "data/rImmediateBuffer.hpp"

class RECONDITE_API rGraphicsDevice{
public:
	virtual ~rGraphicsDevice(){}

	virtual bool Init() = 0;
	virtual bool IsInit() const = 0;
	virtual void Uninit() = 0;
	
	virtual void SwapBuffers() = 0;
	
	virtual void SetClearColor(const rColor& color) = 0;
	virtual void Clear() = 0;
	
	virtual void EnableDepthTesting(bool enable) = 0;
	virtual void EnablePolygonFillOffset(bool enable) = 0;

	virtual unsigned int CreateTexture(int width, int height, int bpp , const unsigned char* data) = 0;
	virtual void UnregisterTexture(int textureID) = 0;
	
	virtual unsigned int CreateShaderProgram(const rString& vertex, const rString& fragment) = 0;
	virtual void DeleteShaderProgram(unsigned int shaderId) = 0;
	virtual void ActivateShader(unsigned int shaderId) = 0;
	
	virtual unsigned int CreateArrayBuffer(const char* data, size_t dataSize) = 0;
	virtual unsigned int CreateElementBuffer(const unsigned short* elementData, size_t elementDataSize) = 0;
	virtual void DeleteBuffer(unsigned int bufferId) = 0;
	
	virtual void RenderGeometry(const rGeometry* geometry, const rMatrix4& transform, const rString& elementBuffer, rMaterial* material) = 0;
	virtual void RenderImmediate(const rImmediateBuffer& geometry, const rMatrix4& transform, rMaterial* material) = 0;
	
	virtual void SetViewport(int x , int y, int width, int height) = 0;
	virtual void SetActiveMaterial(rMaterial* material) = 0;

	virtual unsigned int CreateRenderbuffer(int width, int height) = 0;
	virtual void DeleteRenderbuffer(unsigned int id) = 0;
	virtual unsigned int ReadRenderbufferPixel(unsigned int x, unsigned int y) = 0;
};

#endif
