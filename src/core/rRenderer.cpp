#include "rRenderer.hpp"

rRenderer::rRenderer(rGraphicsDevice* graphicsDevice, rContentManager* contentManager){
	m_graphicsDevice = graphicsDevice;
	m_contentManager = contentManager;
	
	m_activeViewport = NULL;
}

void rRenderer::BeginRenderView (rViewport& viewport){
	m_objectsRendered = 0;
	m_activeViewport = &viewport;
	
	rRect window = viewport.GetScreenRect();
	m_graphicsDevice->SetViewport(window.x, window.y, window.width, window.height);

	viewport.GetViewMatrix(m_viewMatrix);
}

void rRenderer::EndRenderView(){
}

size_t rRenderer::ObjectsRendered() const{
	return m_objectsRendered;
}

void rRenderer::RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBufferName, rMaterial* material){
	rMatrix4 modelViewProjection = m_viewMatrix * transform;
	m_graphicsDevice->RenderGeometry(geometry, modelViewProjection, elementBufferName, material);
}

void rRenderer::RenderBuffer(const rImmediateBuffer& buffer, rMaterial* material){
	m_graphicsDevice->RenderImmediate(buffer, m_viewMatrix, material);
}

void rRenderer::Render3dBuffer(rImmediateBuffer& geometry, const rColor& color){
	rMaterial* material = m_contentManager->GetMaterialAsset("immediate_color");

	if (material){
		material->SetColor("fragColor", color);
		m_graphicsDevice->RenderImmediate(geometry, m_viewMatrix,  material);
	}
}

void rRenderer::RenderModel(const rModel* model, const rMatrix4& transform){
	rMatrix4 modelViewProjection = m_viewMatrix * transform;

	rGeometry* geometry = model->Geometry();
	rArrayString meshNames;
	model->GetMeshNames(meshNames);

	for (size_t i = 0; i < meshNames.size(); i++){
		rMesh* mesh = model->GetMesh(meshNames[i]);

		m_graphicsDevice->RenderGeometry(geometry, modelViewProjection, mesh->buffer, mesh->material);
	}

	m_objectsRendered++;
}

void rRenderer::ImmediateColorRender(rImmediateBuffer& geometry, const rColor& color){
	rMaterial* material = m_contentManager->GetMaterialAsset("immediate_color");
	
	if (material){
		material->SetColor("fragColor", color);
		
		rMatrix4 transform;
		if (m_activeViewport){
			rRect overlay = m_activeViewport->GetScreenRect();
			rMatrixUtil::Ortho2D(overlay.Left(), overlay.Right(), overlay.Bottom(), overlay.Top(), transform);
		}
		
		m_graphicsDevice->RenderImmediate(geometry, transform, material);
	}
}

void rRenderer::ImmediateTexturedRender(rImmediateBuffer& geometry, rTexture2D* texture){
	rMaterial* material = m_contentManager->GetMaterialAsset("immediate_texture");
	
	if (material){
		material->SetTexture("s_texture", texture);
		
		rMatrix4 transform;
		if (m_activeViewport){
			rRect overlay = m_activeViewport->GetScreenRect();
			rMatrixUtil::Ortho2D(overlay.Left(), overlay.Right(), overlay.Bottom(), overlay.Top(), transform);
		}
		
		m_graphicsDevice->RenderImmediate(geometry, transform, material);
	}
}

void rRenderer::RenderRect(const rRect& rect, const rColor& color){
	rImmediateBuffer geometry;
	rGeometryUtil::CreateRectVerticies(rect, geometry, false);
	ImmediateColorRender(geometry, color);
}

void rRenderer::RenderRoundedRect(const rRect& rect, float radius, const rColor& color){
	rImmediateBuffer geometry;
	rGeometryUtil::CreateRoundedRectVerticies(rect, radius, 10, geometry);
	ImmediateColorRender(geometry, color);
}

void rRenderer::RenderRect(const rRect& rect, rTexture2D* texture){
	rImmediateBuffer geometry;
	rGeometryUtil::CreateRectVerticies(rect, geometry, true);
	ImmediateTexturedRender(geometry, texture);
}

void rRenderer::RenderWireRect(const rRect& rect, const rColor& color){
	rImmediateBuffer geometry;
	rGeometryUtil::CreateWireRectVerticies(rect, geometry);
	ImmediateColorRender(geometry, color);
}

void rRenderer::RenderCircle(const rCircle2& circle, const rColor& color){
	rImmediateBuffer geometry;
	rGeometryUtil::CreateCircleVerticies(circle, 20, geometry);
	ImmediateColorRender(geometry, color);
}

void rRenderer::RenderWireBox(const rAlignedBox3& box, const rColor color){
	rImmediateBuffer geometry;
	rGeometryUtil::CreateWireAlignedBoxVerticies(box, geometry);

	rMaterial* material = m_contentManager->GetMaterialAsset("immediate_color");

	if (material){
		material->SetColor("fragColor", color);
		m_graphicsDevice->RenderImmediate(geometry, m_viewMatrix,  material);
	}
}

void rRenderer::CreateRequiredMaterials(){
	rMaterialData materialData;
	materialData.SetShader("default_colored", "");
	materialData.SetParameter( rMATERIAL_PARAMETER_COLOR , "fragColor", "255 255 255 255");
	
	m_contentManager->LoadMaterial(materialData, "immediate_color");
	
	rMaterialData texMaterial;
	texMaterial.SetShader("default_textured", "");
	texMaterial.SetParameter( rMATERIAL_PARAMETER_COLOR , "fragColor", "255 255 255 255");

	m_contentManager->LoadMaterial(texMaterial, "immediate_texture");
	m_contentManager->LoadMaterial(texMaterial, "immediate_text");
}

void rRenderer::RenderString(const rString& str, const rFont* font, const rRect& bounding, const rColor& color){
	if (font){
		rImmediateBuffer geometry;
		rGeometryUtil::Create2DText(str, font, bounding, geometry);

		rMaterial* material = m_contentManager->GetMaterialAsset("immediate_text");
		material->SetColor("fragColor", color);

		if (material){
			material->SetTexture("s_texture", font->Texture());

			rMatrix4 transform;
			if (m_activeViewport){
				rRect overlay = m_activeViewport->GetScreenRect();
				rMatrixUtil::Ortho2D(overlay.Left(), overlay.Right(), overlay.Bottom(), overlay.Top(), transform);
			}

			rMatrix4 translate;
			translate.SetTranslate(bounding.x,bounding.y, 0.0f);
			transform *= translate;

			m_graphicsDevice->RenderImmediate(geometry, transform, material);
		}
	}
}

void rRenderer::RenderString(const rString& text, const rFont* font, const rPoint& pos, const rColor& color){
	rRect bounding(pos.x, pos.y, INT_MAX, INT_MAX);
	RenderString(text, font, bounding, color);
}

void rRenderer::RenderSkeleton(const rSkeleton* skeleton, const rMatrix4Vector& transformArray, const rColor& lineColor, const rColor& pointColor, float pointSize){
	if (skeleton){
		rImmediateBuffer pointData, lineData;
		rGeometryUtil::CreateSkeletonGeometry(skeleton, pointData, lineData);

		for (size_t i = 0; i <transformArray.size(); i++){
			pointData.TransformVertex(i, transformArray[i]);
			lineData.TransformVertex(i, transformArray[i]);
		}

		rMaterial* material = m_contentManager->GetMaterialAsset("immediate_color");
		material->SetColor("fragColor",lineColor);

		m_graphicsDevice->EnableDepthTesting(false);

		m_graphicsDevice->RenderImmediate(lineData, m_viewMatrix, material);

		material = m_contentManager->GetMaterialAsset("default_points");
		material->SetColor("fragColor", pointColor);
		material->SetFloat("recPointSize", pointSize);


		m_graphicsDevice->RenderImmediate(pointData, m_viewMatrix, material);
		m_graphicsDevice->EnableDepthTesting(true);
	}
}
