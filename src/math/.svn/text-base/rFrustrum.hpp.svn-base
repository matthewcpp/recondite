#ifndef R_FRUSTRUM_HPP
#define R_FRUSTRUM_HPP

#include "rPlane3.hpp"
#include "rVector3.hpp"

struct rFrustrum{
	rFrustrum(){}

	bool PointInFrustrum(const rVector3& p);

	rPlane3 near , far, top , bottom, left , right;
};

#endif