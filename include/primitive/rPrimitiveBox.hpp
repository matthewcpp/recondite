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
	void SetBox(const rAlignedBox3& box);

private:
	rAlignedBox3 m_box;
	rColor m_color;
};

#endif