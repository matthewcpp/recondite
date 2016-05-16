#include "rSpriteBatch.hpp"

#include <vector>
#include <map>
#include <memory>

#include "data/rImmediateBuffer.hpp"
#include "rGeometryUtil.hpp"
#include "asset/rFont.hpp"

struct SpriteBatchBuffer{
	rColor color;
	rImmediateBuffer data;

	SpriteBatchBuffer(size_t elementSize, const rColor& _color)
		:data(rGeometryType::Triangles, elementSize, true), color(_color){}
};

struct rSpriteBatch::Impl{
	rContentManager* contentManager;
	rGraphicsDevice* graphicsDevice;

	typedef std::map<rTexture*, std::vector<std::unique_ptr<SpriteBatchBuffer>>> TextureBatchMap;
	TextureBatchMap textBatches;
	TextureBatchMap spriteBatches;

	std::unique_ptr<rMaterial> material;

	Impl(rGraphicsDevice* _graphicsDevice, rContentManager* _contentManager) : graphicsDevice(_graphicsDevice), contentManager(_contentManager), material(new rMaterial()) {}

	rImmediateBuffer* GetBuffer(TextureBatchMap& textureBatch, rTexture* texture, const rColor& color);
	rImmediateBuffer* EnsureTextBuffer(Font::Face* face, const rColor& color);
	rImmediateBuffer* EnsureSpriteBuffer(rTexture* texture, const rColor& color);
};

rImmediateBuffer* rSpriteBatch::Impl::EnsureSpriteBuffer(rTexture* texture, const rColor& color){
	rImmediateBuffer* retBuffer = GetBuffer(spriteBatches, texture, color);

	if (!retBuffer){
		SpriteBatchBuffer* batch = new SpriteBatchBuffer(3, color);
		spriteBatches[texture].emplace_back(batch);

		retBuffer = &batch->data;
	}

	return retBuffer;
}

rImmediateBuffer* rSpriteBatch::Impl::EnsureTextBuffer(Font::Face* face, const rColor& color){
	rTexture* texture = contentManager->Fonts()->GetFontTexture(face);
	rImmediateBuffer* retBuffer = GetBuffer(textBatches, texture, color);

	if (!retBuffer){
		SpriteBatchBuffer* batch =  new SpriteBatchBuffer(2, color);
		textBatches[texture].emplace_back(batch);

		retBuffer = &batch->data;
	}
	
	return retBuffer;
}

rImmediateBuffer* rSpriteBatch::Impl::GetBuffer(TextureBatchMap& textureBatch, rTexture* texture, const rColor& color){
	auto result = textureBatch.find(texture);

	if (result != textureBatch.end()){
		for (size_t i = 0; i < result->second.size(); i++){
			if (result->second[i]->color == color)
				return &result->second[i]->data;
		}
	}

	return nullptr;
}

rSpriteBatch::rSpriteBatch(rGraphicsDevice* graphicsDevice, rContentManager* contentManager){
	_impl = new Impl(graphicsDevice, contentManager);
}

rSpriteBatch::~rSpriteBatch(){
	delete _impl;
}

void rSpriteBatch::RenderTexture(rTexture* texture, const rVector2& position, const rColor& color, float depth) {
	RenderTexture(texture, position, texture->Size(), color, depth);
}

void rSpriteBatch::RenderTexture(rTexture* texture, const rVector2& position, const rSize& size, const rColor& color, float depth) {
	rImmediateBuffer* buffer =_impl->EnsureSpriteBuffer(texture, color);

	rRect rect(position.x, position.y, size.x, size.y);
	rGeometryUtil::CreateRectVerticies(rect, *buffer, true, depth);
}

void rSpriteBatch::Clear() {
	_impl->textBatches.clear();
	_impl->spriteBatches.clear();
}

void rSpriteBatch::Render(const rMatrix4& viewMatrix){
	rShaderManager* shaderManager = _impl->contentManager->Shaders();
	_impl->graphicsDevice->ActivateShader(shaderManager->DefaultSpriteShader()->ProgramId());

	auto end = _impl->spriteBatches.end();

	for (auto it = _impl->spriteBatches.begin(); it != end; ++it) {
		_impl->material->SetDiffuseTexture(it->first);

		for (size_t i = 0; i < it->second.size(); i++){
			_impl->material->SetDiffuseColor(it->second[i]->color);
			_impl->graphicsDevice->RenderImmediate(it->second[i]->data, viewMatrix, _impl->material.get());
		}
	}


	_impl->graphicsDevice->ActivateShader(shaderManager->DefaultTextShader()->ProgramId());

	end = _impl->textBatches.end();

	for (auto it = _impl->textBatches.begin(); it != end; ++it) {
		_impl->material->SetDiffuseTexture(it->first);

		for (size_t i = 0; i < it->second.size(); i++){
			_impl->material->SetDiffuseColor(it->second[i]->color);
			_impl->graphicsDevice->RenderImmediate(it->second[i]->data, viewMatrix, _impl->material.get());
		}
	}
}

void WriteWord(Font::Glyph** glyphs, size_t glyphCount, int startX, int startY, rImmediateBuffer& buffer, const rPoint& origin){
	int xPos = startX;
	int yPos = startY;

	Font::Glyph *glyph = nullptr;

	for (size_t i = 0; i < glyphCount; i++){
		glyph = glyphs[i];

		int left = origin.x + xPos + glyph->leftBearing;
		int right = left + glyph->width;
		int top = origin.y + yPos - glyph->top;
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

void rSpriteBatch::RenderString(const rString& text, Font::Face* face, const rPoint& position, const rSize& size, const rColor& color){
	rTexture* fontTexture = _impl->contentManager->Fonts()->GetFontTexture(face);

	if (fontTexture){
		rImmediateBuffer* buffer = _impl->EnsureTextBuffer(face, color);

		Font::WrapText(face, text, size, [&](Font::Glyph** glyphs, size_t glyphCount, int startX, int startY){
			WriteWord(glyphs, glyphCount, startX, startY, *buffer, position);
		});
	}
}

void rSpriteBatch::RenderString(const rString& text, Font::Face* face, const rPoint& position, const rColor& color){
	rSize maxSize(INT_MAX, INT_MAX);
	RenderString(text, face, position, maxSize, color);
}