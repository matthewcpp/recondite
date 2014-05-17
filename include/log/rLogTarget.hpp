#ifndef R_LOGTARGET_HPP
#define R_LOGTARGET_HPP

#include "rBuild.hpp"

#include "rString.hpp"

class RECONDITE_API rLogTarget{
public:
	virtual void Debug(const rString& message) = 0;
	virtual void Warning(const rString& message) = 0;
	virtual void Trace(const rString& message) = 0;
	virtual void Info(const rString& message) = 0;
	virtual void Error(const rString& message) = 0;
};

#endif
