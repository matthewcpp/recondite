#ifndef R_RENDERER_HPP
#define R_RENDERER_HPP

#include <climits>
#include <memory>
#include <map>

#include "rBuild.hpp"
#include "rDefs.hpp"

#include "rViewport.hpp"
#include "rGraphicsDevice.hpp"
#include "rContentManager.hpp"

#include "rGeometryUtil.hpp"
#include "data/rImmediateBuffer.hpp"
#include "rMatrixUtil.hpp"

#include "rCircle2.hpp"
#include "rAlignedBox3.hpp"

#include "rSkeleton.hpp"
#include "rRenderingOptions.hpp"
#include "rSpriteBatch.hpp"

#include "rModelInstance.hpp"
#include "asset/rMaterial.hpp"
#include "rAnimationController.hpp"

class rDrawable;

using namespace recondite;

class RECONDITE_API rRenderer {
public:
	rRenderer(rGraphicsDevice* graphicsDevice, rContentManager* contentManager);
	
public:

	void SetClearColor(const rColor& color);

	void Begin(const rMatrix4 projection, const rMatrix4& view);
	void Add(rDrawable* drawable);
	void End();

	size_t ObjectsRendered() const;

	void EnableDepthTesting(bool enable);
	bool DepthTestEnabled() const;

	void SetDepthFunction(rGraphicsDevice::DepthFunction depthFunc);
	rGraphicsDevice::DepthFunction GetDepthFunction() const;
	
	rSpriteBatch* SpriteBatch();

	void RenderModel(const ModelInstance* modelInstance, const rMatrix4& matrix);
	void RenderAnimatedModel(const ModelInstance* modelInstance, const rMatrix4& matrix, const recondite::AnimationController* animationController);

	void RenderImmediateLines(const rImmediateBuffer& buffer, rColor color);

	void SetModelRenderMode(rRenderMode renderMode);
	rRenderMode GetModelRenderMode() const;

	rMatrix4 GetProjectionMatrix() const;
	void SetProjectionMatrix(const rMatrix4& projectionMatrix);

	rMatrix4 GetViewMatrix() const;

private:
	void _RenderModel(const ModelInstance* modelInstance, const rMatrix4& matrix);
	void RenderSpriteBatch();

private:
		rGraphicsDevice* m_graphicsDevice;
		rContentManager* m_contentManager;

		rViewport* m_activeViewport;

		rMatrix4 m_viewMatrix;
		rMatrix4 m_projectionMatrix;

		size_t m_objectsRendered;
		std::unique_ptr<rSpriteBatch> m_spriteBatch;
		
		bool m_depthTestEnabled;
		rRenderMode m_defaultRenderMode;
		rGraphicsDevice::DepthFunction depthFunction;

		std::multimap<uint32_t, rDrawable*> m_renderList;
};

#endif
