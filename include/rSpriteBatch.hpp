#ifndef R_SPRITEBATCH_HPP
#define R_SPRITEBATCH_HPP

#include "rBuild.hpp"

#include "asset/rTexture.hpp"
#include "asset/rFont.hpp"

#include "rContentManager.hpp"
#include "rPoint.hpp"


class RECONDITE_API rSpriteBatch {
public:
	rSpriteBatch(rGraphicsDevice* graphicsDevice, rContentManager* contentManager);
	~rSpriteBatch();

public:
	void Clear();

	void RenderTexture(rTexture* texture, const rVector2& position, const rColor& color = rColor::White, float depth = 0.0);
	void RenderTexture(rTexture* texture, const rVector2& position, const rSize& size, const rColor& color = rColor::White, float depth = 0.0);

	void RenderString(const rString& text, Font::Face* face, const rPoint& position, const rColor& color = rColor::White);
	void RenderString(const rString& text, Font::Face* face, const rPoint& position, const rSize& size, const rColor& color = rColor::White);

	void Render(const rMatrix4& viewMatrix);

private:
	
	struct Impl;
	Impl* _impl;
};

#endif