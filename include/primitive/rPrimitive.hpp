#ifndef R_PRIMITIVE_HPP
#define R_PRIMITIVE_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"

class RECONDITE_API rPrimitive : public rActor3{
public:
	rPrimitive(const rString& id, rEngine* engine);

	void SetColor(const rColor& color);
	rColor Color() const;

protected:
	rColor m_color;
};

#endif