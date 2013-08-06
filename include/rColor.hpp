#ifndef R_COLOR_HPP
#define R_COLOR_HPP

struct rColor{
	rColor() {}
	rColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	
	void Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	
	inline unsigned char Red() const;
	inline unsigned char Green() const;
	inline unsigned char Blue() const;
	inline unsigned char Alpha() const;
	
	unsigned char red, green, blue, alpha;
};

unsigned char rColor::Red() const{
	return red;
}

unsigned char rColor::Green() const{
	return green;
}

unsigned char rColor::Blue() const{
	return blue;
}

unsigned char rColor::Alpha() const{
	return alpha;
}

#endif