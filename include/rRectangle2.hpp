#ifndef R_RECTANGLE2_HPP
#define R_RECTANGLE2_HPP

#include "rVector2.hpp"


struct rRectangle2{

	rRectangle2(){}
	rRectangle2(float xx , float yy , float w , float h): x(xx) , y (yy) , width(w) , height(h){} 
	rRectangle2(const rVector2& tl , const rVector2& br);

	float Left() const;
	float Right() const;
	float Bottom() const;
	float Top() const;

	rVector2 TopLeft() const;
	rVector2 TopCenter() const;
	rVector2 TopRight() const;
	
	rVector2 LeftCenter() const;
	rVector2 Center() const;
	rVector2 RightCenter() const;

	rVector2 BottomLeft() const;
	rVector2 BottomCenter() const;
	rVector2 BottomRight() const;

	void Set(const rVector2& tl , const rVector2& br);

	bool ContainsRectangle(const rRectangle2& r) const;
	bool ContainsPoint(const rVector2& p) const;
	bool ContainsPoint(float px , float py) const;

	bool IntersectsRectangle(const rRectangle2& r) const;

	bool operator==(const rRectangle2& r) const;
	bool operator!=(const rRectangle2& r) const;

	static const rRectangle2 NullRectangle;

	float x;
	float y;
	float width;
	float height;
};



#endif