#ifndef R_PRIMITIVECYLINDER_HPP
#define R_PRIMITIVECYLINDER_HPP

#include "rBuild.hpp"

#include "primitive/rPrimitive.hpp"

class RECONDITE_API rPrimitiveCylinder : public rPrimitive{
public:
	rPrimitiveCylinder(const rString& id, rEngine* engine);

public:
	float Radius() const;
	void SetRadius(float radius);

	float Height() const;
	void SetHeight(float height);

	virtual rString ClassName() const;
	virtual void Draw();

private:
	float m_radius;
	float m_height;
};

#endif