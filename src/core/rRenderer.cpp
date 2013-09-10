#include "rRenderer.hpp"

rRenderer::rRenderer(rGraphicsDevice* graphicsDevice, rContentManager* contentManager){
	m_graphicsDevice = graphicsDevice;
	m_contentManager = contentManager;
	
	m_activeViewport = NULL;
	
	CreateRequiredMaterials();
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

void rRenderer::RenderRect(const rRect& rect, const rColor& color){
	rMaterial* material = m_contentManager->GetMaterialAsset("immediate_color");
	
	if (material){
		material->SetColor("fragColor", color);
		
		rGeometryData geometry;
		rGeometryUtil::CreateRectVerticies(rect, "immediate", geometry, false);
		
		rMatrix4 transform;
		if (m_activeViewport){
			rRect overlay = m_activeViewport->GetScreenRect();
			rMatrixUtil::Ortho2D(overlay.Left(), overlay.Right(), overlay.Bottom(), overlay.Top(), transform);
		}
		
		m_graphicsDevice->RenderImmediate(geometry, transform, "immediate", material);
	}
}

void rRenderer::RenderRect(const rRect& rect, rTexture2D* texture){

}

void rRenderer::CreateRequiredMaterials(){
	rMaterialData materialData;
	materialData.SetShader("default_colored", "");
	materialData.SetParameter( rMATERIAL_PARAMETER_COLOR , "fragColor", "255 255 255 255");
	
	m_contentManager->LoadMaterial(materialData, "immediate_color");
}