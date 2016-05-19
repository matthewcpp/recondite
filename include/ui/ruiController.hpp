#ifndef RUI_CONTROLLER_HPP
#define RUI_CONTROLLER_HPP

#include "rBuild.hpp"

class RECONDITE_API ruiController{
public:
	ruiController(const rString& className) : _className(className) {}

public:
	virtual void OnDocumentLoaded() = 0;
	inline rString GetClassName() const;

private:
	rString _className;
};

inline rString ruiController::GetClassName() const{
	return _className;
}

#endif