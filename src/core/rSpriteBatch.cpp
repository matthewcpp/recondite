#include "rSpriteBatch.hpp"

void rSpriteBatch::RenderTexture(rTexture* texture, const rVector2& position, float depth) {
	rVector2 size((float)texture->Width(), (float)texture->Height());
	RenderTexture(texture, position, size, depth);
}

void rSpriteBatch::RenderTexture(rTexture* texture, const rVector2& position, const rVector2& size, float depth) {
	EnsureBuffer(texture);

	rImmediateBuffer& buffer = *(m_buffers[texture].get());

	rRect rect(position.x, position.y, size.x, size.y);
	rGeometryUtil::CreateRectVerticies(rect, buffer, true, depth);
}

void rSpriteBatch::EnsureBuffer(rTexture* texture) {
	if (m_buffers.count(texture) == 0) {
		rImmediateBufferRef buffer;
		buffer.reset(new rImmediateBuffer(rGeometryType::Triangles, 3, true));

		m_buffers[texture] = buffer;
	}
}

void rSpriteBatch::Clear() {
	m_buffers.clear();
}

void rSpriteBatch::ForEach(rSpriteBatchFunction function) {
	auto end = m_buffers.end();

	for (auto it = m_buffers.begin(); it != end; ++it) {
		function(it->first, it->second.get());
	}
}