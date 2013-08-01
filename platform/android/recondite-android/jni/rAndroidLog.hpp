#ifndef R_ANDROIDLOG_HPP
#define R_ANDROIDLOG_HPP

#include <android/log.h>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rLogTarget.hpp"

class rAndroidLog : public rLogTarget{
public:

	void Debug(const rString& message);
	void Warning(const rString& message);
	void Trace(const rString& message);
	void Info(const rString& message);
};

#endif
