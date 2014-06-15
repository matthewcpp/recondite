#ifndef R_PRIMITIVEBOX_HPP
#define R_PRIMITIVEBOX_HPP

#include "rBuild.hpp"
#include "rActor3.hpp"
#include "rAlignedBox3.hpp"

class RECONDITE_API rPrimitiveBox : public rActor3{
public:
	rPrimitiveBox(const rString& name, const rAlignedBox3& box);

public:
	virtual void Draw(rEngine& engine);

private:
	rAlignedBox3 m_box;
};

#endif