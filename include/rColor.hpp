#ifndef R_COLOUR_HPP
#define R_COLOUR_HPP

struct rColour{
	rColour() {}
	rColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	
	void Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	
	inline unsigned char Red() const;
	inline unsigned char Green() const;
	inline unsigned char Blue() const;
	inline unsigned char Alpha() const;
	
	unsigned char red, green, blue, alpha;
};

unsigned char rColour::Red() const{
	return red;
}

unsigned char rColour::Green() const{
	return green;
}

unsigned char rColour::Blue() const{
	return blue;
}

unsigned char rColour::Alpha() const{
	return alpha;
}

#endif