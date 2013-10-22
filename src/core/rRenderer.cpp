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

void rRenderer::ImmediateColorRender(rGeometryData& geometry, const rColor& color){
	rMaterial* material = m_contentManager->GetMaterialAsset("immediate_color");
	
	if (material){
		material->SetColor("fragColor", color);
		
		rMatrix4 transform;
		if (m_activeViewport){
			rRect overlay = m_activeViewport->GetScreenRect();
			rMatrixUtil::Ortho2D(overlay.Left(), overlay.Right(), overlay.Bottom(), overlay.Top(), transform);
		}
		
		m_graphicsDevice->RenderImmediate(geometry, transform, "immediate", material);
	}
}

void rRenderer::ImmediateTexturedRender(rGeometryData& geometry, rTexture2D* texture){
	rMaterial* material = m_contentManager->GetMaterialAsset("immediate_texture");
	
	if (material){
		material->SetTexture("s_texture", texture);
		
		rMatrix4 transform;
		if (m_activeViewport){
			rRect overlay = m_activeViewport->GetScreenRect();
			rMatrixUtil::Ortho2D(overlay.Left(), overlay.Right(), overlay.Bottom(), overlay.Top(), transform);
		}
		
		m_graphicsDevice->RenderImmediate(geometry, transform, "immediate", material);
	}
}

void rRenderer::RenderRect(const rRect& rect, const rColor& color){
	rGeometryData geometry;
	rGeometryUtil::CreateRectVerticies(rect, "immediate", geometry, false);
	ImmediateColorRender(geometry, color);
}

void rRenderer::RenderRect(const rRect& rect, rTexture2D* texture){
	rGeometryData geometry;
	rGeometryUtil::CreateRectVerticies(rect, "immediate", geometry, true);
	ImmediateTexturedRender(geometry, texture);
}

void rRenderer::RenderCircle(const rCircle2& circle, const rColor& color){
	rGeometryData geometry;
	rGeometryUtil::CreateCircleVerticies(circle, 20,"immediate", geometry);
	ImmediateColorRender(geometry, color);
}

void rRenderer::RenderWireBox(const rAlignedBox3& box, const rColor color){
	rGeometryData geometry;
	rGeometryUtil::CreateWireAlignedBoxVerticies(box, "immediate", geometry);

	rMaterial* material = m_contentManager->GetMaterialAsset("immediate_color");

	if (material){
		material->SetColor("fragColor", color);

		rMatrix4 transform, modelViewProjection;
		if (m_activeViewport){
			ComputeWorldSpaceTransformForObject(transform, modelViewProjection);
		}

		m_graphicsDevice->RenderImmediate(geometry, modelViewProjection, "immediate", material);
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

void rRenderer::RenderString(const rString& text, const rFont* font, const rPoint& pos, const rColor& color){
	rGeometryData geometry;

	geometry.Allocate(2, text.size() * 4, true, false);
	rElementBufferData* elements = geometry.CreateElementBuffer("immediate");

	int xPos = 0;
	int yPos = 0;
	int index = 0;

	for (int i = 0; i < text.size(); i++){
		const rFontGlyph* glyph = font->GetGlyph(text[i]);

		int left = xPos + glyph->leftBearing;
		int right = left + glyph->width;
		int top = yPos - glyph->top;
		int bottom = top + glyph->height;


		geometry.SetVertex(index, left, top, glyph->texCoords[0].x, glyph->texCoords[0].y);
		geometry.SetVertex(index + 1, right , top, glyph->texCoords[1].x, glyph->texCoords[1].y);
		geometry.SetVertex(index + 2, right, bottom , glyph->texCoords[2].x, glyph->texCoords[2].y);
		geometry.SetVertex(index + 3, left, bottom, glyph->texCoords[3].x, glyph->texCoords[3].y);

		elements->Push(index, index + 1, index + 2);
		elements->Push(index, index + 2, index + 3);

		index += 4;

		xPos += glyph->advance;
	}

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
		translate.SetTranslate(pos.x,pos.y, 0.0f);
		transform *= translate;

		m_graphicsDevice->RenderImmediate(geometry, transform, "immediate", material);
	}
}
