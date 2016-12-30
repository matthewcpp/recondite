#include "rRenderer.hpp"

#include "rDrawable.hpp"

rRenderer::rRenderer(rGraphicsDevice* graphicsDevice, rContentManager* contentManager){
	m_graphicsDevice = graphicsDevice;
	m_contentManager = contentManager;

	m_spriteBatch.reset(new rSpriteBatch(graphicsDevice, contentManager));
	m_depthTestEnabled = true;

	m_defaultRenderMode = rRenderMode::WireframeOnShaded;
}

void rRenderer::SetModelRenderMode(rRenderMode renderMode) {
	m_defaultRenderMode = renderMode;
}

rRenderMode rRenderer::GetModelRenderMode() const {
	return m_defaultRenderMode;
}

void rRenderer::Begin(const rMatrix4 projection, const rMatrix4& view){
	m_objectsRendered = 0;
	m_spriteBatch->Clear();

	m_projectionMatrix = projection;
	m_viewMatrix = view;
}

void rRenderer::Add(rDrawable* drawable) {
	m_renderList.emplace(drawable->RenderingOptions()->GetLayer(), drawable);
}

void rRenderer::End(){
	for (auto it = m_renderList.begin(), end = m_renderList.end(); it != end; it = m_renderList.upper_bound(it->first)) {
		auto layer = m_renderList.equal_range(it->first);

		for (auto i = layer.first; i != layer.second; ++i) {
			i->second->Draw();
		}

		m_graphicsDevice->Clear(rGraphicsDevice::ClearFlags::Depth);
	}
	m_renderList.clear();
	RenderSpriteBatch();
}

void rRenderer::SetClearColor(const rColor& color) {
	m_graphicsDevice->SetClearColor(color);
}

size_t rRenderer::ObjectsRendered() const{
	return m_objectsRendered;
}

void rRenderer::_RenderModel(const ModelInstance* modelInstance, const rMatrix4& matrix) {
	const recondite::Model* model = modelInstance->GetModel();

	rMatrix4 modelView = m_viewMatrix * matrix;

	const recondite::Geometry* geometry = model->GetGeometry();
	m_graphicsDevice->ActivateGeometryBuffer(geometry);

	size_t triangleMeshCount = model->GetTriangleMeshCount();
	if (m_defaultRenderMode != rRenderMode::Wireframe && triangleMeshCount > 0) {

		for (size_t i = 0; i < model->GetTriangleMeshCount(); i++) {
			const recondite::Mesh* mesh = model->GetTriangleMesh(i);

			m_graphicsDevice->SetActiveMaterial(modelInstance->GetTriangleMeshMaterial(i));
			m_graphicsDevice->RenderTriangleMesh(mesh, m_projectionMatrix, modelView);
		}
	}

	size_t lineMeshCount = model->GetLineMeshCount();
	if (m_defaultRenderMode != rRenderMode::Shaded && lineMeshCount > 0) {
		m_graphicsDevice->ActivateShader(m_contentManager->Shaders()->DefaultLineShader()->ProgramId());

		for (size_t i = 0; i < lineMeshCount; i++) {
			const recondite::Mesh* mesh = model->GetLineMesh(i);

			m_graphicsDevice->SetActiveMaterial(modelInstance->GetLineMeshMaterial(i));
			m_graphicsDevice->RenderLineMesh(mesh, m_projectionMatrix, modelView);
		}
	}

	m_graphicsDevice->DeactivateGeometryBuffer(geometry);
}

void rRenderer::RenderModel(const recondite::ModelInstance* modelInstance, const rMatrix4& matrix) {
	const recondite::Geometry* geometry = modelInstance->GetModel()->GetGeometry();

	rShader* shader = nullptr;

	if (geometry->GetHasTexCoords())
		m_graphicsDevice->ActivateShader(m_contentManager->Shaders()->DefaultModelShader()->ProgramId());
	else
		m_graphicsDevice->ActivateShader(m_contentManager->Shaders()->DefaultPrimitiveShader()->ProgramId());

	_RenderModel(modelInstance, matrix);
}

void rRenderer::RenderAnimatedModel(const ModelInstance* model, const rMatrix4& matrix, const recondite::AnimationController* animationController) {
	m_graphicsDevice->ActivateShader(m_contentManager->Shaders()->DefaultSkinnedShader()->ProgramId());
	m_graphicsDevice->SetSkinningData(animationController->GetBoneTransformData(), animationController->GetBoneTransformCount());
	_RenderModel(model, matrix);
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

void rRenderer::SetDepthFunction(rGraphicsDevice::DepthFunction depthFunc) {
	depthFunction = depthFunc;
	m_graphicsDevice->SetDepthFunction(depthFunc);
}

rGraphicsDevice::DepthFunction rRenderer::GetDepthFunction() const {
	return depthFunction;
}