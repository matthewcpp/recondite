#ifndef R_SPRITEBATCH_HPP
#define R_SPRITEBATCH_HPP

#include "rBuild.hpp"

#include "asset/rTexture.hpp"
#include "asset/rFont.hpp"

#include "rContentManager.hpp"
#include "rPoint.hpp"

#include "rCircle2.hpp"
#include "rRect.hpp"
#include "rColor.hpp"


class RECONDITE_API rSpriteBatch {
public:
	rSpriteBatch(rGraphicsDevice* graphicsDevice, rContentManager* contentManager);
	~rSpriteBatch();

public:
	void Clear();

	void RenderTexture(rTexture* texture, const rVector2& position, const rColor& color = rColor::White, float depth = 0.0);
	void RenderTexture(rTexture* texture, const rVector2& position, const rSize& size, const rColor& color = rColor::White, float depth = 0.0);

	void RenderString(const rString& text, Font::Face* face, const rPoint& position, const rColor& color = rColor::White, float zValue = 0.0f);
	void RenderString(const rString& text, Font::Face* face, const rPoint& position, const rSize& size, const rColor& color = rColor::White, float zValue = 0.0f);

	void Render(const rMatrix4& viewMatrix);

	void RenderCircle(const rCircle2& circle, const rColor& color, float zValue = 0.0f);
	void RenderRectangle(const rRect& rect, const rColor& color, float zValue = 0.0f);
	void RenderWireRectangle(const rRect& rect, const rColor& color, float zValue = 0.0f);
	void RenderRoundedRectangle(const rRect& rect, float radius, const rColor& color, float zValue = 0.0f);
	void RenderWireRoundedRectangle(const rRect& rect, float radius, const rColor& color, float zValue = 0.0f);
	

private:
	
	struct Impl;
	Impl* _impl;
};

#endif