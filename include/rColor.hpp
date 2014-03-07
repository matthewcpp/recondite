#ifndef R_COLOR_HPP
#define R_COLOR_HPP

struct rColor{
	rColor() {}
	rColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	:red(r), green(g), blue (b), alpha(a){}
	
	void Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void Set(const unsigned char* color);

	void ToArray(unsigned char* color) const;
	
	unsigned char red, green, blue, alpha;

	static const rColor White;
	static const rColor Red;
	static const rColor Green;
	static const rColor Blue;
	static const rColor Black;
};

#endif
