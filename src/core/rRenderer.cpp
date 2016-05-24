#include "rRenderer.hpp"

rRenderer::rRenderer(rGraphicsDevice* graphicsDevice, rContentManager* contentManager){
	m_graphicsDevice = graphicsDevice;
	m_contentManager = contentManager;

	m_spriteBatch.reset(new rSpriteBatch(graphicsDevice, contentManager));
	
}

void rRenderer::Begin(const rMatrix4 projection, const rMatrix4& view){
	m_objectsRendered = 0;
	m_spriteBatch->Clear();

	m_projectionMatrix = projection;
	m_viewMatrix = view;


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

void rRenderer::RenderPrimitive(const rModel* model, rRenderingOptions* renderingOptions, const rMatrix4& matrix){
	m_graphicsDevice->ActivateShader(m_contentManager->Shaders()->DefaultPrimitiveShader()->ProgramId());

	rMatrix4 modelView = m_viewMatrix * matrix;

	rArrayString meshNames;
	model->GetMeshNames(meshNames);

	rGeometry* geometry = model->Geometry();


	for (size_t i = 0; i < meshNames.size(); i++){
		rMesh* mesh = model->GetMesh(meshNames[i]);

		if (mesh->GeometryType() == rGeometryType::Triangles){
			m_graphicsDevice->RenderGeometry(geometry, m_projectionMatrix, modelView, mesh->Buffer(), mesh->Material());
			m_objectsRendered++;
		}
	}
}


rSpriteBatch* rRenderer::SpriteBatch() {
	return m_spriteBatch.get();
}

void rRenderer::RenderSpriteBatch() {
	rMatrix4 viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	m_spriteBatch->Render(viewProjectionMatrix);
}

void rRenderer::EnableDepthTesting(bool enable){
	m_graphicsDevice->EnableDepthTesting(enable);
}