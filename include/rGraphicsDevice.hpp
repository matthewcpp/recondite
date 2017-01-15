#ifndef R_GRAPHICSDEVICE_HPP
#define R_GRAPHICSDEVICE_HPP

#include <cmath>
#include <vector>

#include "rBuild.hpp"
#include "rDefs.hpp"

#include "rViewport.hpp"
#include "rAlignedBox3.hpp"

#include "asset/rMaterial.hpp"
#include "asset/rModel.hpp"
#include "asset/rGeometryData.hpp"

#include "data/rImmediateBuffer.hpp"

class RECONDITE_API rGraphicsDevice{
public:
	enum class DepthFunction {
		Less,
		LessEqual
	};

	enum ClearFlags {
		Color = 1,
		Depth = 2,
		All = 0xFFFF
	};
public:
	virtual ~rGraphicsDevice(){}

	virtual bool Init() = 0;
	virtual bool IsInit() const = 0;
	virtual void Uninit() = 0;
	
	virtual void SwapBuffers() = 0;
	
	virtual void SetClearColor(const rColor& color) = 0;
	virtual void Clear(ClearFlags flags = ClearFlags::All) = 0;
	
	virtual void EnableDepthTesting(bool enable) = 0;
	virtual void SetDepthFunction(DepthFunction depthFunction) = 0;
	

	virtual unsigned int CreateTexture(int width, int height, int bpp , const unsigned char* data) = 0;
	virtual void UnregisterTexture(int textureID) = 0;
	
	virtual unsigned int CreateShaderProgram(const rString& vertex, const rString& fragment) = 0;
	virtual void DeleteShaderProgram(unsigned int shaderId) = 0;
	virtual void ActivateShader(unsigned int shaderId) = 0;
	virtual void SetSkinningData(const rMatrix4* matrices, size_t count) = 0;
	
	virtual unsigned int CreateArrayBuffer(const char* data, size_t dataSize) = 0;
	virtual unsigned int CreateElementBuffer(const char* elementData, size_t elementDataSize) = 0;
	virtual unsigned int CreateGeometryBuffer(const recondite::GeometryData* geometryData) = 0;
	virtual void DeleteBuffer(unsigned int bufferId) = 0;
	
	virtual void ActivateGeometryBuffer(const recondite::Geometry* geometry) = 0;
	virtual void DeactivateGeometryBuffer(const recondite::Geometry* geometry) = 0;

	virtual void RenderTriangleMesh(const recondite::Mesh* mesh, const rMatrix4& projection, const rMatrix4& modelview) = 0;
	virtual void RenderLineMesh(const recondite::Mesh* mesh, const rMatrix4& projection, const rMatrix4& modelview) = 0;

	virtual void RenderImmediate(const rImmediateBuffer& geometry, const rMatrix4& transform, rMaterial* material) = 0;
	
	virtual void SetViewport(int x , int y, int width, int height) = 0;
	virtual void SetActiveMaterial(const rMaterial* material) = 0;

	virtual unsigned int CreateFramebuffer(int width, int height) = 0;
	virtual bool DeleteFramebuffer(unsigned int id) = 0;
	virtual void ReadActiveFramebuffer(const rRect& rect, unsigned char* buffer) = 0;
	virtual bool ActivateFramebuffer(unsigned int id) = 0;
	virtual bool GetFramebufferSize(unsigned int id, rSize& size) = 0;
	virtual unsigned int GetActiveFramebufferId() = 0;
};

#endif
