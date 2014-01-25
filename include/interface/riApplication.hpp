#ifndef RI_APPLICATION_HPP
#define RI_APPLICATION_HPP

#include "rSize.hpp"

class riApplication{
public:
	virtual rSize DisplaySize() const = 0; 
};

#endif