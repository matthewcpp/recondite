#ifndef R_SIZE_HPP
#define R_SIZE_HPP

struct rSize{
	rSize(){}
	rSize(int xx , int yy) : x(xx) , y(yy){}
	
	void Set(int xx , int yy);

	int x;
	int y;

	bool operator == (const rSize& sz) const;
	bool operator != (const rSize& sz) const;

	static const rSize Default;
};

#endif
