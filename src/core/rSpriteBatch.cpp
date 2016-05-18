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
	~SpriteBatchBuffer(){}
};

struct rSpriteBatch::Impl{
	rContentManager* contentManager;
	rGraphicsDevice* graphicsDevice;

	typedef std::map<rTexture*, std::vector<std::unique_ptr<SpriteBatchBuffer>>> TextureBatchMap;
	typedef std::map<int, std::unique_ptr<rImmediateBuffer>> DrawingBatchMap;

	TextureBatchMap textBatches;
	TextureBatchMap spriteBatches;
	DrawingBatchMap lineBatches;
	DrawingBatchMap drawingBatches;

	std::unique_ptr<rMaterial> material;

	Impl(rGraphicsDevice* _graphicsDevice, rContentManager* _contentManager) : graphicsDevice(_graphicsDevice), contentManager(_contentManager), material(new rMaterial()) {}

	int HashColor(const rColor& color);
	void UnhashColor(int hashVal, rColor& color);

	rImmediateBuffer* EnsureTextureBatchBuffer(TextureBatchMap& textureBatch, rTexture* texture, const rColor& color);
	rImmediateBuffer* EnsureDrawingBatchBuffer(DrawingBatchMap& drawingBatch, const rColor& color, rGeometryType geometryType);
};

rImmediateBuffer* rSpriteBatch::Impl::EnsureTextureBatchBuffer(TextureBatchMap& textureBatch, rTexture* texture, const rColor& color){
	auto result = textureBatch.find(texture);

	if (result != textureBatch.end()){
		for (size_t i = 0; i < result->second.size(); i++){
			if (result->second[i]->color == color)
				return &result->second[i]->data;
		}
	}

	SpriteBatchBuffer* batch = new SpriteBatchBuffer(3, color);
	textureBatch[texture].emplace_back(batch);
	return &batch->data;
}

int rSpriteBatch::Impl::HashColor(const rColor& color){
	int hashVal;
	memcpy(&hashVal, &color, sizeof(int));

	return hashVal;
}

void rSpriteBatch::Impl::UnhashColor(int hashVal, rColor& color){
	memcpy(&color, &hashVal, sizeof(int));
}

rImmediateBuffer* rSpriteBatch::Impl::EnsureDrawingBatchBuffer(DrawingBatchMap& drawingBatch, const rColor& color, rGeometryType geometryType){
	int hashVal = HashColor(color);
	auto result = drawingBatch.find(hashVal);

	if (result == drawingBatch.end()){
		rImmediateBuffer* buffer = new rImmediateBuffer(geometryType, 3, false);
		std::unique_ptr<rImmediateBuffer> bufferRef(buffer);

		drawingBatch.insert(std::make_pair(hashVal, std::move(bufferRef)));
		return buffer;
	}
	else{
		return result->second.get();
	}
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
	rImmediateBuffer* buffer = _impl->EnsureTextureBatchBuffer(_impl->spriteBatches, texture, color);

	rRect rect(position.x, position.y, size.x, size.y);
	rGeometryUtil::CreateRectVerticies(rect, *buffer, true, depth);
}

void rSpriteBatch::Clear() {
	_impl->textBatches.clear();
	_impl->spriteBatches.clear();
	_impl->lineBatches.clear();
	_impl->drawingBatches.clear();
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

	_impl->graphicsDevice->ActivateShader(shaderManager->DefaultDrawingShader()->ProgramId());
	_impl->material->SetDiffuseTexture(nullptr);

	for (auto& it : _impl->drawingBatches){
		rColor color;
		_impl->UnhashColor(it.first, color);

		_impl->material->SetDiffuseColor(color);
		_impl->graphicsDevice->RenderImmediate(*it.second.get(), viewMatrix, _impl->material.get());
	}

	for (auto& it : _impl->lineBatches){
		rColor color;
		_impl->UnhashColor(it.first, color);

		_impl->material->SetDiffuseColor(color);
		_impl->graphicsDevice->RenderImmediate(*it.second.get(), viewMatrix, _impl->material.get());
	}
}

void WriteWord(Font::Glyph** glyphs, size_t glyphCount, int startX, int startY, rImmediateBuffer& buffer, const rPoint& origin, float zValue){
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

		buffer.PushVertex(left, top, zValue, glyph->uvOrigin.x, glyph->uvOrigin.y);
		buffer.PushVertex(right, top, zValue, glyph->uvOrigin.x + glyph->uvSize.x, glyph->uvOrigin.y);
		buffer.PushVertex(right, bottom, zValue, glyph->uvOrigin.x + glyph->uvSize.x, glyph->uvOrigin.y - glyph->uvSize.y);
		buffer.PushVertex(left, bottom, zValue, glyph->uvOrigin.x, glyph->uvOrigin.y - glyph->uvSize.y);

		buffer.PushIndex(index, index + 1, index + 2);
		buffer.PushIndex(index, index + 2, index + 3);

		xPos += glyph->advance;
	}
}

void rSpriteBatch::RenderString(const rString& text, Font::Face* face, const rPoint& position, const rSize& size, const rColor& color, float zValue){
	rTexture* fontTexture = _impl->contentManager->Fonts()->GetFontTexture(face);

	if (fontTexture){
		rImmediateBuffer* buffer = _impl->EnsureTextureBatchBuffer(_impl->textBatches, fontTexture, color);

		Font::WrapText(face, text, size, [&](Font::Glyph** glyphs, size_t glyphCount, int startX, int startY){
			WriteWord(glyphs, glyphCount, startX, startY, *buffer, position, zValue);
		});
	}
}

void rSpriteBatch::RenderString(const rString& text, Font::Face* face, const rPoint& position, const rColor& color, float zValue){
	rSize maxSize(INT_MAX, INT_MAX);
	RenderString(text, face, position, maxSize, color, zValue);
}

void rSpriteBatch::RenderRectangle(const rRect& rect, const rColor& color, float zValue){
	rImmediateBuffer* buffer = _impl->EnsureDrawingBatchBuffer(_impl->drawingBatches, color, rGeometryType::Triangles);
	rGeometryUtil::CreateRectVerticies(rect, *buffer, false, zValue);
}

void rSpriteBatch::RenderWireRectangle(const rRect& rect, const rColor& color, float zValue){
	rImmediateBuffer* buffer = _impl->EnsureDrawingBatchBuffer(_impl->drawingBatches, color, rGeometryType::Lines);
	rGeometryUtil::CreateWireRectVerticies(rect, *buffer, zValue);
}

void rSpriteBatch::RenderRoundedRectangle(const rRect& rect, float radius, const rColor& color, float zValue){
	rImmediateBuffer* buffer = _impl->EnsureDrawingBatchBuffer(_impl->drawingBatches, color, rGeometryType::Triangles);
	rGeometryUtil::CreateRoundedRectVerticies(rect, radius, 16, *buffer, zValue);
}

void rSpriteBatch::RenderCircle(const rCircle2& circle, const rColor& color, float zValue){
	rImmediateBuffer* buffer = _impl->EnsureDrawingBatchBuffer(_impl->drawingBatches, color, rGeometryType::Triangles);
	rGeometryUtil::CreateCircleVerticies(circle, 32, *buffer, zValue);
}