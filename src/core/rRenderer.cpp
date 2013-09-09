#include "rRenderer.hpp"

rRenderer::rRenderer(rGraphicsDevice* graphicsDevice){
	m_graphicsDevice = graphicsDevice;
	m_activeViewport = NULL;
}

void rRenderer::Render (rViewport& viewport){
	m_activeViewport = &viewport;
	
	rRect window = viewport.GetScreenRect();
	m_graphicsDevice->SetViewport(window.x, window.y, window.width, window.height);
}

void rRenderer::RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBufferName, rMaterial* material){
	rMatrix4 modelViewProjection;
	ComputeWorldSpaceTransformForObject(transform, modelViewProjection);
	
	m_graphicsDevice->RenderGeometry(geometry, modelViewProjection, elementBufferName, material);
}

void rRenderer::ComputeWorldSpaceTransformForObject(const rMatrix4& object, rMatrix4& world){
		if (m_activeViewport){
			rMatrix4 view, projection;
			m_activeViewport->GetViewMatrix(view);
			m_activeViewport->GetProjectionMatrix(projection);

			world = view * object;
			world = projection * world;
		}
		else{
			world = object;
		}
}