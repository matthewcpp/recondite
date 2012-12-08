#ifndef R_RECT_HPP
#define R_RECT_HPP

struct rRect{
	rRect();
	rRect (int xx, int yy, int wwidth, int hheight) : x(xx), y(yy), width(wwidth), height(hheight){}
	
	int x , y;
	int width, height;
};

#endif
