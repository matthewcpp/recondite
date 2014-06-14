#ifndef R_RENDERER_HPP
#define R_RENDERER_HPP

#include <climits>

#include "rBuild.hpp"

#include "rViewport.hpp"
#include "rGraphicsDevice.hpp"
#include "rContentManager.hpp"

#include "rGeometryUtil.hpp"
#include "data/rImmediateBuffer.hpp"
#include "rMatrixUtil.hpp"

#include "rCircle2.hpp"
#include "rAlignedBox3.hpp"

#include "rSkeleton.hpp"
#include "rAnimationPlayer.hpp"

class RECONDITE_API rRenderer {
public:
	rRenderer(rGraphicsDevice* graphicsDevice, rContentManager* contentManager);
	
public:
	void CreateRequiredMaterials();

	void BeginRenderView (rViewport& viewport);
	void EndRenderView();
	size_t ObjectsRendered() const;
	
	void RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBufferName, rMaterial* material);
	
	void RenderRect(const rRect& rect, const rColor& color);
	void RenderWireRect(const rRect& rect, const rColor& color);
	void RenderRect(const rRect& rect, rTexture2D* texture);

	void RenderRoundedRect(const rRect& rect, float radius, const rColor& color);
	
	void RenderCircle(const rCircle2& circle, const rColor& color);

	void RenderString(const rString& text, const rFont* font, const rPoint& pos, const rColor& color);
	void RenderString(const rString& str, const rFont* font, const rRect& bounding, const rColor& color);

	void RenderWireBox(const rAlignedBox3& box, const rColor color);

	void RenderModel(const rModel* model, const rMatrix4& transform);
	void RenderBuffer(const rImmediateBuffer& buffer, rMaterial* material);

	void RenderSkeleton(const rSkeleton* skeleton, const rMatrix4Vector& transformArray, const rColor& lineColor, const rColor& pointColor, float pointSize);

private:
	void ComputeWorldSpaceTransformForObject(const rMatrix4& object, rMatrix4& world);
	
	void ImmediateColorRender(rImmediateBuffer& geometry, const rColor& color);
	void ImmediateTexturedRender(rImmediateBuffer& geometry, rTexture2D* texture);

private:
		rGraphicsDevice* m_graphicsDevice;
		rContentManager* m_contentManager;
		rViewport* m_activeViewport;

		size_t m_objectsRendered;
};

#endif
