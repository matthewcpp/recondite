#ifndef R_GRAPHICSDEVICE_HPP
#define R_GRAPHICSDEVICE_HPP

#include <cmath>
#include <vector>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rViewport.hpp"
#include "rMaterial.hpp"
#include "rAlignedBox3.hpp"
#include "rGeometry.hpp"

#include "data/rGeometryData.hpp"
#include "data/rImmediateBuffer.hpp"

class rGraphicsDevice{
public:
	virtual ~rGraphicsDevice(){}

	virtual bool Init() = 0;
	virtual bool IsInit() const = 0;
	virtual void Uninit()  = 0;
	
	virtual void SwapBuffers() = 0;
	
	virtual void SetClearColor(const rColor& color) = 0;
	virtual void SetClearColor(float r, float g, float b, float a) = 0;
	virtual void Clear()  = 0;
	
	virtual void EnableDepthTesting(bool enable) = 0;

	virtual unsigned int CreateTexture(int width, int height, int bpp , const unsigned char* data) = 0;
	virtual void UnregisterTexture(int textureID) = 0;
	
	virtual unsigned int CreateShaderProgram(const rString& vertex, const rString& fragment) = 0;
	virtual void DeleteShaderProgram(unsigned int shaderId) = 0;
	
	virtual unsigned int CreateArrayBuffer(const char* data, size_t dataSize) = 0;
	virtual unsigned int CreateElementBuffer(const unsigned short* elementData, size_t elementDataSize) = 0;
	virtual void DeleteBuffer(unsigned int bufferId) = 0;
	
	virtual void RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBuffer, rMaterial* material) = 0;
	virtual void RenderImmediate(rImmediateBuffer& geometry, const rMatrix4& transform, rMaterial* material) = 0;
	
	virtual void SetViewport(int x , int y, int width, int height) = 0;
	virtual void SetActiveMaterial(rMaterial* material) = 0;
};

#endif
