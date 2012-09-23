#ifndef R_INTERSECTION2_HPP
#define R_INTERSECTION2_HPP

#include "rRectangle2.hpp"
#include "rCircle2.hpp"
#include "rVector2.hpp"
#include "rLine2.hpp"

#include "rMathUtil.hpp"

namespace rIntersection2{
	
	bool RectangleInstersectsCircle(const rRectangle2& r , const rCircle2& c);
	bool RectangleContainsCircle(const rRectangle2& r , const rCircle2& c);
	bool LineSegmentInstersectsCircle(const rLineSegment2& ls , const rCircle2& c);
	
}

#endif