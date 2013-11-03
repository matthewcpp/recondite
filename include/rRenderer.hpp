#ifndef R_RENDERER_HPP
#define R_RENDERER_HPP

#include <climits>

#include "rDefs.hpp"
#include "rTypes.hpp"

#include "rViewport.hpp"
#include "rGraphicsDevice.hpp"
#include "rContentManager.hpp"

#include "rGeometryUtil.hpp"
#include "data/rGeometryData.hpp"
#include "rMatrixUtil.hpp"

#include "rCircle2.hpp"
#include "rAlignedBox3.hpp"

#include "rSkeleton.hpp"

class rRenderer {
public:
	rRenderer(rGraphicsDevice* graphicsDevice, rContentManager* contentManager);
	
public:
	void Render (rViewport& viewport);
	
	void RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBufferName, rMaterial* material);
	
	void RenderRect(const rRect& rect, const rColor& color);
	void RenderWireRect(const rRect& rect, const rColor& color);
	void RenderRect(const rRect& rect, rTexture2D* texture);
	
	void RenderCircle(const rCircle2& circle, const rColor& color);

	void RenderString(const rString& text, const rFont* font, const rPoint& pos, const rColor& color);

	void RenderWireBox(const rAlignedBox3& box, const rColor color);

	void RenderModel(const rModel* model, const rMatrix4& transform);

	void RenderSkeleton(const rSkeleton* skeleton, const rMatrix4& transform, const rColor& color);

private:
	void ComputeWorldSpaceTransformForObject(const rMatrix4& object, rMatrix4& world);
	
	void CreateRequiredMaterials();
	void ImmediateColorRender(rGeometryData& geometry, const rColor& color);
	void ImmediateTexturedRender(rGeometryData& geometry, rTexture2D* texture);

private:
		rGraphicsDevice* m_graphicsDevice;
		rContentManager* m_contentManager;
		rViewport* m_activeViewport;
};

#endif
