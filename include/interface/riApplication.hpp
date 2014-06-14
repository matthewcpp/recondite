#ifndef RI_APPLICATION_HPP
#define RI_APPLICATION_HPP

#include "rBuild.hpp"

#include "rSize.hpp"
#include "rViewport.hpp"

class RECONDITE_API riApplication{
public:
	virtual rSize DisplaySize() const = 0; 
	virtual size_t TargetFPS() const = 0;
	virtual size_t FrameCount() const = 0;

	virtual rViewport* CreateViewport(const rString& name) = 0;
	virtual rViewport* GetViewport(const rString& name) const = 0;
	virtual void DeleteViewport(const rString& name) = 0;
	virtual size_t NumViewports() const = 0;
};

#endif