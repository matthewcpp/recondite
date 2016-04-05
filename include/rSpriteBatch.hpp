#ifndef R_SPRITEBATCH_HPP
#define R_SPRITEBATCH_HPP

#include <map>
#include <memory>
#include <functional>

#include "rBuild.hpp"
#include "asset/rTexture.hpp"
#include "data/rImmediateBuffer.hpp"
#include "rGeometryUtil.hpp"

class RECONDITE_API rSpriteBatch {
public:
	typedef std::function<void(rTexture*, rImmediateBuffer*)> rSpriteBatchFunction;
public:
	void ForEach(rSpriteBatchFunction function);
	void Clear();

	void RenderTexture(rTexture* texture, const rVector2& position);
	void RenderTexture(rTexture* texture, const rVector2& position, const rVector2& size);


private:
	void EnsureBuffer(rTexture* texture);

private:
	typedef std::shared_ptr<rImmediateBuffer> rImmediateBufferRef;
	typedef std::map<rTexture*, rImmediateBufferRef> rImmediateBufferMap;

private:
	rImmediateBufferMap m_buffers;
};

#endif