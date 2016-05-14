#include "rSpriteBatch.hpp"

#include <vector>

#include "data/rImmediateBuffer.hpp"
#include "rGeometryUtil.hpp"
#include "asset/rFont.hpp"

struct rSpriteBatch::Impl{
	rContentManager* contentManager;
	rGraphicsDevice* graphicsDevice;

	std::map<rTexture*, std::shared_ptr<rImmediateBuffer>> spriteBuffers;
	std::map<rTexture*, std::shared_ptr<rImmediateBuffer>> textBuffers;

	Impl(rGraphicsDevice* _graphicsDevice, rContentManager* _contentManager) : graphicsDevice(_graphicsDevice), contentManager(_contentManager) {}

	void EnsureSpriteBuffer(rTexture* texture);
	void EnsureTextBuffer(Font::Face* face);
};

void rSpriteBatch::Impl::EnsureSpriteBuffer(rTexture* texture){
	if (spriteBuffers.count(texture) == 0) {
		std::shared_ptr<rImmediateBuffer> buffer;
		buffer.reset(new rImmediateBuffer(rGeometryType::Triangles, 3, true));

		spriteBuffers[texture] = buffer;
	}
}

void rSpriteBatch::Impl::EnsureTextBuffer(Font::Face* face){
	rTexture* texture = contentManager->Fonts()->GetFontTexture(face);

	if (textBuffers.count(texture) == 0) {
		std::shared_ptr<rImmediateBuffer> buffer;
		buffer.reset(new rImmediateBuffer(rGeometryType::Triangles, 2, true));

		textBuffers[texture] = buffer;
	}
}

rSpriteBatch::rSpriteBatch(rGraphicsDevice* graphicsDevice, rContentManager* contentManager){
	_impl = new Impl(graphicsDevice, contentManager);
}

rSpriteBatch::~rSpriteBatch(){
	delete _impl;
}

void rSpriteBatch::RenderTexture(rTexture* texture, const rVector2& position, float depth) {
	rVector2 size((float)texture->Width(), (float)texture->Height());
	RenderTexture(texture, position, size, depth);
}

void rSpriteBatch::RenderTexture(rTexture* texture, const rVector2& position, const rVector2& size, float depth) {
	_impl->EnsureSpriteBuffer(texture);

	rImmediateBuffer& buffer = *(_impl->spriteBuffers[texture].get());

	rRect rect(position.x, position.y, size.x, size.y);
	rGeometryUtil::CreateRectVerticies(rect, buffer, true, depth);
}

void rSpriteBatch::Clear() {
	_impl->spriteBuffers.clear();
	_impl->textBuffers.clear();
}

void rSpriteBatch::Render(const rMatrix4& viewMatrix){
	rMaterial* spriteMaterial = _impl->contentManager->Materials()->Get("sprite_material");
	if (!spriteMaterial) {
		spriteMaterial = _impl->contentManager->Materials()->CreateMaterial("sprite_material");
		spriteMaterial->SetShader(_impl->contentManager->Shaders()->DefaultSpriteShader());
	}

	_impl->graphicsDevice->ActivateShader(spriteMaterial->Shader()->ProgramId());
	auto end = _impl->spriteBuffers.end();

	for (auto it = _impl->spriteBuffers.begin(); it != end; ++it) {
		spriteMaterial->SetDiffuseTexture(it->first);
		
		_impl->graphicsDevice->RenderImmediate(*it->second, viewMatrix, spriteMaterial);
	}

	rMaterial* textMaterial = _impl->contentManager->Materials()->Get("default_text");
	if (!textMaterial) {
		textMaterial = _impl->contentManager->Materials()->CreateMaterial("default_text");
		textMaterial->SetShader(_impl->contentManager->Shaders()->Get("default_textured"));
	}
	_impl->graphicsDevice->ActivateShader(textMaterial->Shader()->ProgramId());

	end = _impl->textBuffers.end();
	for (auto it = _impl->textBuffers.begin(); it != end; ++it) {
		textMaterial->SetDiffuseTexture(it->first);

		_impl->graphicsDevice->RenderImmediate(*it->second, viewMatrix, textMaterial);
	}
}

void WriteWord(Font::Glyph** glyphs, size_t glyphCount, rImmediateBuffer& buffer, int startX, int startY){
	int xPos = startX;
	int yPos = startY;

	Font::Glyph *glyph = nullptr;

	for (size_t i = 0; i < glyphCount; i++){
		glyph = glyphs[i];

		int left = xPos + glyph->leftBearing;
		int right = left + glyph->width;
		int top = yPos - glyph->top;
		int bottom = top + glyph->height;

		size_t index = buffer.VertexCount();

		buffer.PushVertex(left, top, glyph->uvOrigin.x, glyph->uvOrigin.y);
		buffer.PushVertex(right, top, glyph->uvOrigin.x + glyph->uvSize.x, glyph->uvOrigin.y);
		buffer.PushVertex(right, bottom, glyph->uvOrigin.x + glyph->uvSize.x, glyph->uvOrigin.y - glyph->uvSize.y);
		buffer.PushVertex(left, bottom, glyph->uvOrigin.x, glyph->uvOrigin.y - glyph->uvSize.y);

		buffer.PushIndex(index, index + 1, index + 2);
		buffer.PushIndex(index, index + 2, index + 3);

		xPos += glyph->advance;
	}
}

void rSpriteBatch::RenderString(Font::Face* face, const rString& text, const rPoint& position, const rSize& size){
	rTexture* fontTexture = _impl->contentManager->Fonts()->GetFontTexture(face);

	if (fontTexture){
		_impl->EnsureTextBuffer(face);

		rImmediateBuffer& buffer = *(_impl->textBuffers[fontTexture].get());

		Font::WrapText(face, text, size, [&](Font::Glyph** glyphs, size_t glyphCount, int startX, int startY){
			WriteWord(glyphs, glyphCount, buffer, startX, startY);
		});
	}
}

void rSpriteBatch::RenderString(Font::Face* face, const rString& text, const rPoint& position){
	rSize maxSize(INT_MAX, INT_MAX);
	RenderString(face, text, position, maxSize);
}