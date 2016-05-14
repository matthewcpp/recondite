#ifndef R_COLOR_HPP
#define R_COLOR_HPP

#include <stdint.h>

#include "rBuild.hpp"

struct RECONDITE_API rColor{
	rColor() {}
	rColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	:red(r), green(g), blue (b), alpha(a){}
	
	void Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void Set(const unsigned char* color);

	void ToArray(unsigned char* color) const;
	
	uint8_t red, green, blue, alpha;

	bool operator==(const rColor& color);
	bool operator!=(const rColor& color);

	static const rColor White;
	static const rColor Red;
	static const rColor Green;
	static const rColor Blue;
	static const rColor Black;
	static const rColor Transparent;
};

class rColorComparator{
public:
	//returns true if c1 < c2
	bool operator()(const rColor& c1, const rColor& c2){
		if (c1.red < c2.red)
			return true;
		if (c1.red > c2.red)
			return false;

		if (c1.green < c2.green)
			return true;
		if (c1.green > c2.green)
			return false;

		if (c1.blue < c2.blue)
			return true;
		if (c1.blue > c2.blue)
			return false;

		if (c1.alpha < c2.alpha)
			return true;
		if (c1.alpha > c2.alpha)
			return false;

		return false;
	}
};

#endif
