#ifndef R_FRUSTRUM_HPP
#define R_FRUSTRUM_HPP

#include "rBuild.hpp"

#include "rPlane.hpp"
#include "rVector3.hpp"

struct RECONDITE_API rFrustrum{
	rFrustrum(){}

	bool PointInFrustrum(const rVector3& p);

	rPlane near;
	rPlane far; 
	rPlane top; 
	rPlane bottom;
	rPlane left;
	rPlane right;
};

#endif