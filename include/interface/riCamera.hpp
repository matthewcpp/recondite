#ifndef RI_CAMERA_HPP
#define RI_CAMERA_HPP

#include "rBuild.hpp"

#include "rVector3.hpp"

class RECONDITE_API riCamera{
public:
	virtual rVector3 Position() const = 0;
	virtual rVector3 Target() const = 0;
	virtual rVector3 Up() const = 0;
};

#endif

