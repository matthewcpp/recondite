#ifndef R_RECT_HPP
#define R_RECT_HPP

#include "rBuild.hpp"
#include "rPoint.hpp"
#include "rSize.hpp"

struct RECONDITE_API rRect{
	rRect() {}
	rRect(int xx, int yy, int wwidth, int hheight) : x(xx), y(yy), width(wwidth), height(hheight) {}
	rRect(const rPoint& point, const rSize& size);
	
	void Set(int xx, int yy, int wwidth, int hheight);
	void Set(const rPoint& point, const rSize& size);
	
	void SetPosition(const rPoint& point);
	void SetPosition(int xx, int yy);
	
	void SetSize(const rSize& size);
	void SetSize(int wwidth, int hheight);
	rSize Size() const;
	
	bool ContainsPoint(const rPoint& point);
	
	rPoint Center() const;
	
	int Left() const;
	int Right() const;
	int Bottom() const;
	int Top() const;
	
	int x , y;
	int width, height;
};

#endif
