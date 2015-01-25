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
	virtual void DeleteViewport(const rString& name) = 0;
	virtual size_t NumViewports() const = 0;

	virtual void LoadScene(const rString& name) = 0;

	virtual void RegisterActorLoader(const rString& className, riActorLoader* actorLoader) = 0;
	virtual void UnregisterActorLoader(const rString& className) = 0;

	//temporary
	//TODO: handle multiple display?
	virtual rSize DisplaySize() const = 0;
};

#endif