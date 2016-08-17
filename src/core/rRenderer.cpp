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

void rRenderer::RenderModel(const recondite::Model* model, const rMatrix4& matrix) {
	rMatrix4 modelView = m_viewMatrix * matrix;

	const recondite::Geometry* geometry = model->GetGeometry();

	if (geometry->GetHasTexCoords())
		m_graphicsDevice->ActivateShader(m_contentManager->Shaders()->DefaultModelShader()->ProgramId());
	else
		m_graphicsDevice->ActivateShader(m_contentManager->Shaders()->DefaultPrimitiveShader()->ProgramId());

	m_graphicsDevice->ActivateGeometryBuffer(geometry);

	for (size_t i = 0; i < model->GetTriangleMeshCount(); i++) {
		const recondite::Mesh* mesh = model->GetTriangleMesh(i);

		m_graphicsDevice->SetActiveMaterial(mesh->GetMaterial());
		m_graphicsDevice->RenderMesh(mesh, m_projectionMatrix, modelView);
	}

	m_graphicsDevice->DeactivateGeometryBuffer(geometry);
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