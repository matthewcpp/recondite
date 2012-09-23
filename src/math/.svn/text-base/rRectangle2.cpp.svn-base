#include "rRectangle2.hpp"


rRectangle2::rRectangle2(const rVector2& tl , const rVector2& br){
	Set(tl , br);
}


void rRectangle2::Set(const rVector2& tl , const rVector2& br){
	x = tl.x;
	y = tl.y;
	width = br.x - tl.x;
	height = br.y - tl.y;
}


float rRectangle2::Left() const{
	return x;
}


float rRectangle2::Right() const{
	return x + width;
}


float rRectangle2::Bottom() const{
	return y + height;
}


float rRectangle2::Top() const{
	return y;
}


rVector2 rRectangle2::TopLeft() const{
	return rVector2(x , y);
}


rVector2 rRectangle2::TopCenter() const{
	return rVector2(x + width / 2 , y);
}


rVector2 rRectangle2::TopRight() const{
	return rVector2(x + width , y);
}


rVector2 rRectangle2::LeftCenter() const{
	return rVector2( x , y + (height / 2) );
}


rVector2 rRectangle2::RightCenter() const{
	return rVector2( x + width  , y + (height / 2) );
}


rVector2 rRectangle2::Center() const{
	return rVector2( x + (width / 2) , y + (height / 2) );
}


rVector2 rRectangle2::BottomLeft() const{
	return rVector2(x , y + height);
}


rVector2 rRectangle2::BottomCenter() const{
	return rVector2(x + width / 2 , y + height);
}


rVector2 rRectangle2::BottomRight() const{
	return rVector2(x + width , y + height);
}


bool rRectangle2::operator==(const rRectangle2& r) const{
	return x == r.x && y == r.y && width == r.width && height == r.height;
}


bool rRectangle2::operator!=(const rRectangle2& r) const{
	return !(*this == r);
}


bool rRectangle2::ContainsRectangle(const rRectangle2& r) const{
		if (r.x < x || r.y < y)
			return false;

		return r.x + r.width <= x + width &&
				r.y + r.height <= y + height;
}


bool rRectangle2::ContainsPoint(float px , float py) const{
	rVector2 p(px , py);

	return ContainsPoint(p);
}


bool rRectangle2::ContainsPoint(const rVector2& p) const{
		if (p.x < x || p.y < y)
			return false;

		return p.x <= x + width &&
				p.y <= y + height;
}


bool rRectangle2::IntersectsRectangle(const rRectangle2& r) const{
	return !(	r.Left() > Right() || 
			   r.Right() < Left() || 
			   r.Top() > Bottom() ||
			   r.Bottom() < Top() );
}

const rRectangle2 rRectangle2::NullRectangle = rRectangle2(0.0f , 0.0f , 0.0f, 0.0f);