#ifndef R_LINE3_HPP
#define R_LINE3_HPP

#include "rBuild.hpp"

#include "rVector3.hpp"

struct RECONDITE_API rRay3{
	rRay3(){}
	rRay3(const rVector3& p , const rVector3& d) : origin(p) , direction(d){}

	void Set(const rVector3& p , const rVector3& d);

	rVector3 origin;
	rVector3 direction;
};

struct RECONDITE_API rLineSegment3{
	rLineSegment3(){}
        rLineSegment3(const rVector3& _p0 , const rVector3& _p1) : p0(_p0) , p1(_p1){}

        void Set(const rVector3& _p0 , const rVector3& _p1);

	rVector3 p0;
	rVector3 p1;
};

#endif