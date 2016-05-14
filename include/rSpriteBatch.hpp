#ifndef R_SPRITEBATCH_HPP
#define R_SPRITEBATCH_HPP

#include <map>
#include <memory>

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

	void RenderTexture(rTexture* texture, const rVector2& position, float depth = 0.0);
	void RenderTexture(rTexture* texture, const rVector2& position, const rVector2& size, float depth = 0.0);

	void RenderString(Font::Face* face, const rString& text, const rPoint& position);
	void RenderString(Font::Face* face, const rString& text, const rPoint& position, const rSize& size);

	void Render(const rMatrix4& viewMatrix);

private:
	
	struct Impl;
	Impl* _impl;
};

#endif