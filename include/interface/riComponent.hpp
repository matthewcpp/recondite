#ifndef RI_APPLICATION_HPP
#define RI_APPLICATION_HPP

#include "rBuild.hpp"

#include "rSize.hpp"
#include "rViewport.hpp"

class riActorLoader;

class RECONDITE_API riComponent{
public:
	virtual rViewport* CreateViewport(const rString& name) = 0;
	virtual rViewport* GetViewport(const rString& name) const = 0;
	virtual void GetViewportNames(rArrayString& names) const = 0;
	virtual void DeleteViewport(const rString& name) = 0;
	virtual size_t NumViewports() const = 0;

	virtual void LoadScene(const rString& name) = 0;

	//temporary
	virtual rSize DisplaySize() const = 0;
	virtual rString GetBasePath() = 0;
};

#endif