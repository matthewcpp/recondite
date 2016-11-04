#include "rRenderer.hpp"

rRenderer::rRenderer(rGraphicsDevice* graphicsDevice, rContentManager* contentManager){
	m_graphicsDevice = graphicsDevice;
	m_contentManager = contentManager;

	m_spriteBatch.reset(new rSpriteBatch(graphicsDevice, contentManager));
	m_depthTestEnabled = true;
}

void rRenderer::Begin(const rMatrix4 projection, const rMatrix4& view){
	m_objectsRendered = 0;
	m_spriteBatch->Clear();

	m_projectionMatrix = projection;
	m_viewMatrix = view;
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

	size_t triangleMeshCount = model->GetTriangleMeshCount();
	if (triangleMeshCount > 0) {
		
		if (geometry->GetHasTexCoords())
			m_graphicsDevice->ActivateShader(m_contentManager->Shaders()->DefaultModelShader()->ProgramId());
		else
			m_graphicsDevice->ActivateShader(m_contentManager->Shaders()->DefaultPrimitiveShader()->ProgramId());

		m_graphicsDevice->ActivateGeometryBuffer(geometry);

		for (size_t i = 0; i < model->GetTriangleMeshCount(); i++) {
			const recondite::Mesh* mesh = model->GetTriangleMesh(i);

			m_graphicsDevice->SetActiveMaterial(mesh->GetMaterial());
			m_graphicsDevice->RenderTriangleMesh(mesh, m_projectionMatrix, modelView);
		}
	}


	size_t lineMeshCount = model->GetLineMeshCount();
	if (lineMeshCount > 0) {
		m_graphicsDevice->ActivateShader(m_contentManager->Shaders()->DefaultLineShader()->ProgramId());

		for (size_t i = 0; i < lineMeshCount; i++) {
			const recondite::Mesh* mesh = model->GetLineMesh(i);
			
			m_graphicsDevice->SetActiveMaterial(mesh->GetMaterial());
			m_graphicsDevice->RenderLineMesh(mesh, m_projectionMatrix, modelView);
		}
	}

	m_graphicsDevice->DeactivateGeometryBuffer(geometry);
}

void rRenderer::RenderImmediateLines(const rImmediateBuffer& buffer, rColor color) {
	m_graphicsDevice->ActivateShader(m_contentManager->Shaders()->DefaultLineShader()->ProgramId());

	rMatrix4 viewProjection = m_projectionMatrix * m_viewMatrix;

	rMaterial material;
	material.SetDiffuseColor(color);
	m_graphicsDevice->RenderImmediate(buffer, viewProjection, &material);
}


rSpriteBatch* rRenderer::SpriteBatch() {
	return m_spriteBatch.get();
}

void rRenderer::RenderSpriteBatch() {
	rMatrix4 viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	m_spriteBatch->Render(viewProjectionMatrix);
}

void rRenderer::EnableDepthTesting(bool enable){
	m_depthTestEnabled = enable;
	m_graphicsDevice->EnableDepthTesting(enable);
}

bool rRenderer::DepthTestEnabled() const {
	return m_depthTestEnabled;
}