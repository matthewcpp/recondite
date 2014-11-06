#ifndef R_PRIMITIVEBOX_HPP
#define R_PRIMITIVEBOX_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"
#include "rAlignedBox3.hpp"

class RECONDITE_API rPrimitiveBox : public rActor3{
public:
	rPrimitiveBox(const rString& id, rEngine* engine);

public:
	virtual void Draw();

	void SetColor(const rColor& color);
	rColor Color() const;

	virtual rString ClassName() const;
	rAlignedBox3 Box() const;

	float Width() const;
	void SetWidth(float width);

	float Height() const;
	void SetHeight(float height);

	float Depth() const;
	void SetDepth(float depth);

private:
	rColor m_color;

	float m_width;
	float m_height;
	float m_depth;
};

#endif