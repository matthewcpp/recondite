#ifndef R_RENDERER_HPP
#define R_RENDERER_HPP

#include "rDefs.hpp"
#include "rTypes.hpp"

#include "rViewport.hpp"
#include "rGraphicsDevice.hpp"

class rRenderer {
public:
	rRenderer(rGraphicsDevice* graphicsDevice);
	
public:
	void Render (rViewport& viewport);
	
	void RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBufferName, rMaterial* material);

private:
	void ComputeWorldSpaceTransformForObject(const rMatrix4& object, rMatrix4& world);

private:
		rGraphicsDevice* m_graphicsDevice;
		rViewport* m_activeViewport;
};

#endif