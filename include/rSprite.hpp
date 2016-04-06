#ifndef R_SPRITE_HPP
#define R_SPRITE_HPP

#include "rBuild.hpp"

#include "rActor3.hpp"

class RECONDITE_API rSprite : public rActor3 {
public:
	rSprite(const rString& id, rEngine* engine);
	rSprite(const rString& id, rEngine* engine, rTexture* texture);

public:
	virtual void SetPosition2d(const rVector2& position);
	virtual rVector2 Position2d() const;

	void SetSize(const rVector2& size);
	void SetSize(float x, float y);
	rVector2 GetSize() const;

	void SetRenderDepth(float depth);
	float RenderDepth() const;

	rTexture* GetTexture() const;
	void SetTexture(rTexture* texture);

	virtual void Draw() override;

	virtual rString ClassName() const override;

private:
	rVector2 m_size;
	bool m_sizeSet;
	rTexture* m_texture;
};

#endif