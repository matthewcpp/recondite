#ifndef R_LOG_HPP
#define R_LOG_HPP

#include <cstddef>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rLogTarget.hpp"

class rLog{
public:
	static void SetLogTarget(rLogTarget* target);
	
	static void Debug(const rString& message);
	static void Warning(const rString& message);
	static void Trace(const rString& message);
	static void Info(const rString& message);
	
	static void SetEnabled(bool enabled);
	static bool Enabled();
	
private:
	static rLogTarget* m_logTarget;
	static bool m_enabled;
};

#endif
