#ifndef R_RENDERER_HPP
#define R_RENDERER_HPP

#include <climits>

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

	void BeginRenderView (rViewport& viewport);
	void EndRenderView();
	size_t ObjectsRendered() const;

	void EnableDepthTesting(bool enable);
	
	void RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBufferName, rMaterial* material);
	void RenderShadedWithEdges(rGeometry* geometry, const rMatrix4& transform, rMaterial* material, const rColor& edgeColor);

	void RenderRect(const rRect& rect, const rColor& color);
	void RenderWireRect(const rRect& rect, const rColor& color);
	void RenderRect(const rRect& rect, rTexture* texture);

	rSpriteBatch* SpriteBatch();

	void RenderRoundedRect(const rRect& rect, float radius, const rColor& color);
	
	void RenderCircle(const rCircle2& circle, const rColor& color);

	void RenderString(const rString& text, const rFont* font, const rPoint& pos, const rColor& color);
	void RenderString(const rString& str, const rFont* font, const rRect& bounding, const rColor& color);

	void RenderWireBox(const rAlignedBox3& box, const rColor color);

	void RenderModel(const rModel* model, rRenderingOptions* renderingOptions, const rMatrix4& transform);
	void RenderWireframeOnShaded(const rModel* model, const rMatrix4& transform);

	void RenderBuffer(const rImmediateBuffer& buffer, rMaterial* material);
	void Render3dBuffer(rImmediateBuffer& geometry, const rMatrix4& transform, const rColor& color);

	void RenderSkeleton(const rSkeleton* skeleton, const rMatrix4Vector& transformArray, const rColor& lineColor, const rColor& pointColor, float pointSize);

private:
	void ForceRenderModel(const rModel* model, const rMatrix4& modelViewProjection);

	void RenderLineMeshes(const rModel* model, const rMatrix4& modelViewProjection);
	void RenderTriangleMeshes(const rModel* model, const rMatrix4& modelViewProjection);

private:	
	void ImmediateColorRender(rImmediateBuffer& geometry, const rColor& color);
	void ImmediateTexturedRender(rImmediateBuffer& geometry, rTexture* texture);

	void RenderSpriteBatch();

private:
		rGraphicsDevice* m_graphicsDevice;
		rContentManager* m_contentManager;

		rViewport* m_activeViewport;
		rRenderMode m_renderMode;

		rMatrix4 m_viewMatrix;
		rMatrix4 m_viewProjectionMatrix;


		size_t m_objectsRendered;
		rSpriteBatch m_spriteBatch;
};

#endif
