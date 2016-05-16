#include "rRenderer.hpp"

rRenderer::rRenderer(rGraphicsDevice* graphicsDevice, rContentManager* contentManager){
	m_graphicsDevice = graphicsDevice;
	m_contentManager = contentManager;

	m_spriteBatch.reset(new rSpriteBatch(graphicsDevice, contentManager));
	
}

void rRenderer::Begin(const rMatrix4 viewProjectionMatrix){
	m_objectsRendered = 0;
	m_spriteBatch->Clear();

	m_viewProjectionMatrix = viewProjectionMatrix;

	//m_renderMode = viewport->RenderMode();
}

void rRenderer::End(){
	RenderSpriteBatch();
}

void rRenderer::SetClearColor(const rColor& color) {
	m_graphicsDevice->SetClearColor(color);
}

size_t rRenderer::ObjectsRendered() const{
	return m_objectsRendered;
}

void rRenderer::RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBufferName, rMaterial* material){
	rMatrix4 modelViewProjection = m_viewProjectionMatrix * transform;
	m_graphicsDevice->RenderGeometry(geometry, modelViewProjection, elementBufferName, material);
}

void rRenderer::RenderShadedWithEdges(rGeometry* geometry, const rMatrix4& transform, rMaterial* material, const rColor& edgeColor){

}

void rRenderer::ForceRenderModel(const rModel* model, const rMatrix4& modelViewProjection){
	rArrayString meshNames;
	model->GetMeshNames(meshNames);

	rGeometry* geometry = model->Geometry();

	for (size_t i = 0; i < meshNames.size(); i++){
		rMesh* mesh = model->GetMesh(meshNames[i]);

		//m_graphicsDevice->ActivateShader(mesh->Material()->Shader()->ProgramId());
		m_graphicsDevice->RenderGeometry(geometry, modelViewProjection, mesh->Buffer(), mesh->Material());
		m_objectsRendered++;
	}
}

void rRenderer::RenderLineMeshes(const rModel* model, const rMatrix4& modelViewProjection){
	rArrayString meshNames;
	model->GetMeshNames(meshNames);

	rGeometry* geometry = model->Geometry();

	for (size_t i = 0; i < meshNames.size(); i++){
		rMesh* mesh = model->GetMesh(meshNames[i]);
		rGeometryType geometryType = mesh->GeometryType();

		if (geometryType == rGeometryType::Lines || geometryType == rGeometryType::LineLoop){
			//m_graphicsDevice->ActivateShader(mesh->Material()->Shader()->ProgramId());
			m_graphicsDevice->RenderGeometry(geometry, modelViewProjection, mesh->Buffer(), mesh->Material());
			m_objectsRendered++;
		}
	}
}

void rRenderer::RenderTriangleMeshes(const rModel* model, const rMatrix4& modelViewProjection){
	rArrayString meshNames;
	model->GetMeshNames(meshNames);

	rGeometry* geometry = model->Geometry();

	for (size_t i = 0; i < meshNames.size(); i++){
		rMesh* mesh = model->GetMesh(meshNames[i]);

		if (mesh->GeometryType() == rGeometryType::Triangles){
			//m_graphicsDevice->ActivateShader(mesh->Material()->Shader()->ProgramId());
			m_graphicsDevice->RenderGeometry(geometry, modelViewProjection, mesh->Buffer(), mesh->Material());
			m_objectsRendered++;
		}
	}
}


void rRenderer::RenderModel(const rModel* model, rRenderingOptions* renderingOptions, const rMatrix4& transform){
	if (!renderingOptions->Visible()) return;

	m_graphicsDevice->EnableDepthTesting(renderingOptions->Overdraw());

	rMatrix4 modelViewProjection = m_viewProjectionMatrix * transform;

	if (renderingOptions->ForceRender()){
		ForceRenderModel(model, modelViewProjection);
	}
	else if (m_renderMode == rRenderMode::Wireframe){
		RenderLineMeshes(model, modelViewProjection);
	}
	else if (m_renderMode == rRenderMode::Shaded){
		RenderTriangleMeshes(model, modelViewProjection);
	}
}

void rRenderer::ImmediateColorRender(rImmediateBuffer& geometry, const rColor& color){

}

rSpriteBatch* rRenderer::SpriteBatch() {
	return m_spriteBatch.get();
}

void rRenderer::RenderSpriteBatch() {
	m_spriteBatch->Render(m_viewProjectionMatrix);
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

}

void rRenderer::EnableDepthTesting(bool enable){
	m_graphicsDevice->EnableDepthTesting(enable);
}

void rRenderer::SetMatrix(const rMatrix4& matrix){
	m_viewProjectionMatrix = matrix;
}