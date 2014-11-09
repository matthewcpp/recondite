#ifndef R_PRIMITIVE_HPP
#define R_PRIMITIVE_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"

class RECONDITE_API rPrimitive : public rActor3{
public:
	rPrimitive(const rString& id, rEngine* engine);

	void SetColor(const rColor& color);
	rColor Color() const;

	virtual void Draw();

protected:
	virtual void CreateGeometry() = 0;
	void InvalidateGeometry();

	//temp
	rImmediateBuffer geometry;

private:
	rColor m_color;
	bool m_geometryInvalid;
};

#endif