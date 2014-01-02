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

void rRenderer::RenderModel(const rModel* model, const rMatrix4& transform){
	rMatrix4 modelViewProjection;
	ComputeWorldSpaceTransformForObject(transform, modelViewProjection);

	rGeometry* geometry = model->Geometry();
	rArrayString meshNames;
	model->GetMeshNames(meshNames);

	for (size_t i = 0; i < meshNames.size(); i++){
		rMesh* mesh = model->GetMesh(meshNames[i]);

		m_graphicsDevice->RenderGeometry(geometry, modelViewProjection, mesh->buffer, mesh->material);
	}
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

void rRenderer::RenderWireRect(const rRect& rect, const rColor& color){
	rGeometryData geometry;
	rGeometryUtil::CreateWireRectVerticies(rect, "immediate", geometry);
	ImmediateColorRender(geometry, color);
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

void rRenderer::RenderString(const rString& str, const rFont* font, const rRect& bounding, const rColor& color){
	if (font){
		rGeometryData geometry;
		rGeometryUtil::Create2DText(str, font, bounding, "immediate", geometry);

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

			m_graphicsDevice->RenderImmediate(geometry, transform, "immediate", material);
		}
	}
}

void rRenderer::RenderString(const rString& text, const rFont* font, const rPoint& pos, const rColor& color){
	rRect bounding(pos.x, pos.y, INT_MAX, INT_MAX);
	RenderString(text, font, bounding, color);
}

void rRenderer::RenderSkeleton(const rSkeleton* skeleton, const rMatrix4Vector& transformArray, const rColor& color){
	if (skeleton){
		rGeometryData geometryData;
		rGeometryUtil::CreateSkeletonGeometry(skeleton, "skeleton", geometryData);

		for (size_t i = 0; i <transformArray.size(); i++)
			geometryData.TransformVertex(i, transformArray[i]);

		rMatrix4 modelViewProjection, transform;
		if (m_activeViewport){
			ComputeWorldSpaceTransformForObject(transform, modelViewProjection);
		}

		rMaterial* material = m_contentManager->GetMaterialAsset("immediate_color");
		material->SetColor("fragColor",color);

		m_graphicsDevice->EnableDepthTesting(false);

		m_graphicsDevice->RenderImmediate(geometryData, modelViewProjection, "skeleton_wire", material);

		material = m_contentManager->GetMaterialAsset("default_points");
		material->SetColor("fragColor",color);
		material->SetFloat("recPointSize",5.0f);


		m_graphicsDevice->RenderImmediate(geometryData, modelViewProjection, "skeleton_points", material);
		m_graphicsDevice->EnableDepthTesting(true);
	}
}
