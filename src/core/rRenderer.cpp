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

void rRenderer::WriteWord(rFontGlyphArray& glyphs, rGeometryData& geometry, int startX, int startY){
	rElementBufferData* elements = geometry.GetElementBuffer("immediate");

	int xPos = startX;
	int yPos = startY;

	rFontGlyph* glyph = NULL;
	for (size_t i = 0; i < glyphs.size(); i++){
		glyph = glyphs[i];

		int left = xPos + glyph->leftBearing;
		int right = left + glyph->width;
		int top = yPos - glyph->top;
		int bottom = top + glyph->height;

		unsigned short index = geometry.Push(left, top, glyph->texCoords[0].x, glyph->texCoords[0].y);
		geometry.Push(right , top, glyph->texCoords[1].x, glyph->texCoords[1].y);
		geometry.Push(right, bottom , glyph->texCoords[2].x, glyph->texCoords[2].y);
		geometry.Push(left, bottom, glyph->texCoords[3].x, glyph->texCoords[3].y);

		elements->Push(index, index + 1, index + 2);
		elements->Push(index, index + 2, index + 3);

		xPos += glyph->advance;
	}

	glyphs.clear();
}

void rRenderer::RenderString(const rString& str, const rFont* font, const rRect& bounding, const rColor& color){
	rGeometryData geometry;
	rFontGlyphArray wordGlyphs;

	geometry.SetVertexDataInfo(2, true, false);
	rElementBufferData* elements = geometry.CreateElementBuffer("immediate");

	int xPos = 0;
	int yPos = font->LineHeight();

	int wordWidth = 0;
	int spaceLeft = bounding.width;

	for (int i = 0; i < str.size(); i++){
		int c = str[i];

		if (c == '\n'){
			if (wordWidth > spaceLeft ){ //current word will not fit on this line
				yPos += font->LineHeight();
				xPos = 0;
			}

			WriteWord(wordGlyphs, geometry, xPos, yPos);

			yPos += font->LineHeight();
			xPos = 0;
			spaceLeft = bounding.width;
			wordWidth = 0;

		}
		else{
			rFontGlyph* glyph = font->GetGlyph(c);

			if (c == ' '){
				if (wordWidth + glyph->advance > spaceLeft ){ //current word will not fit on this line
					yPos += font->LineHeight();
					xPos = 0;
					spaceLeft = bounding.width;
				}

				WriteWord(wordGlyphs, geometry, xPos, yPos);

				spaceLeft -= wordWidth + glyph->advance;
				xPos += wordWidth + glyph->advance;;
				wordWidth = 0;

			}
			else{
				wordWidth += glyph->advance;
				wordGlyphs.push_back(glyph);
			}
		}
	}

	WriteWord(wordGlyphs, geometry, xPos, yPos);

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

void rRenderer::RenderString(const rString& text, const rFont* font, const rPoint& pos, const rColor& color){
	rRect bounding(pos.x, pos.y, INT_MAX, INT_MAX);
	RenderString(text, font, bounding, color);
}

void BuildBoneGeometry(rGeometryData& geometryData, rBone* bone, unsigned short parentVertexIndex){
	size_t vertexIndex = geometryData.Push(bone->WoldPosition());

	geometryData.GetElementBuffer("skeleton_points")->Push(vertexIndex);

	if (parentVertexIndex != USHRT_MAX){
		geometryData.GetElementBuffer("skeleton_wire")->Push(parentVertexIndex, vertexIndex);
	}

	for (size_t i = 0; i < bone->children.size(); i++){
		BuildBoneGeometry(geometryData, bone->children[i], vertexIndex);
	}
}

void rRenderer::RenderSkeleton(const rSkeleton* skeleton, const rMatrix4& transform, const rColor& color){
	if (skeleton){
		rBoneArray bones;
		skeleton->GetTopLevelBones(bones);

		rGeometryData geometryData;
		geometryData.SetVertexDataInfo(3,false,false);

		geometryData.CreateElementBuffer("skeleton_wire")->SetGeometryType(rGEOMETRY_LINES);
		geometryData.CreateElementBuffer("skeleton_points")->SetGeometryType(rGEOMETRY_POINTS);

		for (size_t i = 0; i < bones.size(); i++){
			BuildBoneGeometry(geometryData, bones[i], USHRT_MAX);
		}

		rMatrix4 modelViewProjection;
		if (m_activeViewport){
			ComputeWorldSpaceTransformForObject(transform, modelViewProjection);
		}

		rMaterial* material = m_contentManager->GetMaterialAsset("immediate_color");
		material->SetColor("fragColor",color);

		m_graphicsDevice->RenderImmediate(geometryData, modelViewProjection, "skeleton_wire", material);
	}
}
