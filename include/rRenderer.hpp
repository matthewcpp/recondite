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
#include "rAnimationPlayer.hpp"
#include "rSpriteBatch.hpp"

#include "asset/rModel.hpp"

class RECONDITE_API rRenderer {
public:
	rRenderer(rGraphicsDevice* graphicsDevice, rContentManager* contentManager);
	
public:

	void SetClearColor(const rColor& color);

	void Begin(const rMatrix4 viewProjectionMatrix);
	void End();
	void SetMatrix(const rMatrix4& matrix);

	size_t ObjectsRendered() const;

	void EnableDepthTesting(bool enable);
	
	void RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBufferName, rMaterial* material);
	void RenderShadedWithEdges(rGeometry* geometry, const rMatrix4& transform, rMaterial* material, const rColor& edgeColor);

	rSpriteBatch* SpriteBatch();

	void RenderWireBox(const rAlignedBox3& box, const rColor color);

	void RenderModel(const rModel* model, rRenderingOptions* renderingOptions, const rMatrix4& transform);
	void RenderWireframeOnShaded(const rModel* model, const rMatrix4& transform);

private:
	void ForceRenderModel(const rModel* model, const rMatrix4& modelViewProjection);

	void RenderLineMeshes(const rModel* model, const rMatrix4& modelViewProjection);
	void RenderTriangleMeshes(const rModel* model, const rMatrix4& modelViewProjection);

private:	
	void ImmediateColorRender(rImmediateBuffer& geometry, const rColor& color);

	void RenderSpriteBatch();

private:
		rGraphicsDevice* m_graphicsDevice;
		rContentManager* m_contentManager;

		rViewport* m_activeViewport;
		rRenderMode m_renderMode;

		rMatrix4 m_viewProjectionMatrix;

		size_t m_objectsRendered;
		std::unique_ptr<rSpriteBatch> m_spriteBatch;
};

#endif
