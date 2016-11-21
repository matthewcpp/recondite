#ifndef R_RENDERER_HPP
#define R_RENDERER_HPP

#include <climits>
#include <memory>

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

#include "asset/rModel.hpp"
#include "asset/rMaterial.hpp"
#include "rAnimationController.hpp"

using namespace recondite;

class RECONDITE_API rRenderer {
public:
	rRenderer(rGraphicsDevice* graphicsDevice, rContentManager* contentManager);
	
public:

	void SetClearColor(const rColor& color);

	void Begin(const rMatrix4 projection, const rMatrix4& view);
	void End();

	size_t ObjectsRendered() const;

	void EnableDepthTesting(bool enable);
	bool DepthTestEnabled() const;
	
	rSpriteBatch* SpriteBatch();

	void RenderModel(const Model* model, const rMatrix4& matrix);
	void RenderAnimatedModel(const Model* model, const rMatrix4& matrix, const recondite::AnimationController* animationController);

	void RenderImmediateLines(const rImmediateBuffer& buffer, rColor color);

	void SetDefaultRenderMode(rRenderMode renderMode);

private:
	void _RenderModel(const Model* model, const rMatrix4& matrix);
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
};

#endif
