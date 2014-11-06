#ifndef R_PRIMITIVECONE_HPP
#define R_PRIMITIVECONE_HPP

#include "rBuild.hpp"

#include "primitive/rPrimitive.hpp"

class rPrimitiveCone : public rPrimitive{
public:
	rPrimitiveCone(const rString& id, rEngine* engine);

	float Radius() const;
	void SetRadius(float radius);

	float Height() const;
	void SetHeight(float height);

	virtual rString ClassName() const;
	virtual void Draw();

private:
	float m_height;
	float m_radius;
};

#endif