#include "rIntersection2.hpp"

bool rIntersection2::RectangleInstersectsCircle(const rRectangle2& r , const rCircle2& c){
	//trivial case, center not within rectangle
	if (r.ContainsPoint(c.center))
		return true;

	//check TL & TR
	rLineSegment2 seg( r.TopLeft() , r.TopRight() );
	if (rIntersection2::LineSegmentInstersectsCircle(seg, c))
		return true;

	//check BR & TR
	seg.s1 = r.BottomRight();
	if (rIntersection2::LineSegmentInstersectsCircle(seg, c))
		return true;

	//check BR & BL
	seg.s2 = r.BottomLeft();
	if (rIntersection2::LineSegmentInstersectsCircle(seg, c))
		return true;

	//check TL & BL
	seg.s1 = r.TopLeft();
	if (rIntersection2::LineSegmentInstersectsCircle(seg, c))
		return true;

	return false;
}

bool rIntersection2::RectangleContainsCircle(const rRectangle2& r , const rCircle2& c){
	//trivial case, center not within rectangle
	if (!r.ContainsPoint(c.center))
		return false;

	//make sure the radius does not extend beyond any of the rectangles edges
	return	c.center.x + c.radius < r.Right() &&
			c.center.x - c.radius > r.Left() &&
			c.center.y + c.radius < r.Bottom() &&
			c.center.y - c.radius > r.Top();
}


bool rIntersection2::LineSegmentInstersectsCircle(const rLineSegment2& ls , const rCircle2& c){
	
	/*
	rVector2 closest = rMath::ClosestPointOnSegment(ls ,c);

	if(c.center.Distance(closest) < c.radius)
		return true;
		*/

	return false;
}