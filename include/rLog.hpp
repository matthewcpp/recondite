#ifndef R_LOG_HPP
#define R_LOG_HPP

#include <cstddef>
#include <stdarg.h>
#include <cstdio>

#include "rBuild.hpp"
#include "rString.hpp"

#include "log/rLogTarget.hpp"

class RECONDITE_API rLog{
public:
	static void SetLogTarget(rLogTarget* target);
	
	static void Debug(const rString format, ...);
	static void Warning(const rString format, ...);
	static void Trace(const rString format, ...);
	static void Info(const rString format, ...);
	static void Error(const rString format, ...);
	
	static void SetEnabled(bool enabled);
	static bool Enabled();
	
private:
	static rString FormatString(const rString format, va_list args);
	
private:
	static rLogTarget* m_logTarget;
	static bool m_enabled;
};

#endif
