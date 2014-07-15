#ifndef R_LOGSTDOUT_HPP
#define R_LOGSTDOUT_HPP

#include <iostream>

#include "rBuild.hpp"
#include "log/rLogTarget.hpp"

class RECONDITE_API rLogStdOut : public rLogTarget{
public:
	virtual void Debug(const rString& message);
	virtual void Warning(const rString& message);
	virtual void Trace(const rString& message);
	virtual void Info(const rString& message);
	virtual void Error(const rString& message);

	virtual void Shutdown();
};

#endif