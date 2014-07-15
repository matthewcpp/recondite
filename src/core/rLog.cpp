#include "rLog.hpp"

rLogTarget* rLog::m_logTarget = NULL;
bool rLog::m_enabled = true;

void rLog::SetLogTarget(rLogTarget* target){
	m_logTarget = target;
}

void rLog::Debug(const rString format, ...){
	if (m_enabled && m_logTarget){
		va_list args;
		va_start(args, format);
		
		rString message = FormatString(format, args);
		m_logTarget->Debug(message);
		
		va_end(args);
		}
}

void rLog::Warning(const rString format, ...){
	if (m_enabled && m_logTarget){
		va_list args;
		va_start(args, format);
			
		rString message = FormatString(format, args);
		m_logTarget->Warning(message);
		
		va_end(args);
	}
}

void rLog::Trace(const rString format, ...){
	if (m_enabled && m_logTarget){
		va_list args;
		va_start(args, format);
			
		rString message = FormatString(format, args);
		m_logTarget->Trace(message);
		
		va_end(args);
	}
}

void rLog::Info(const rString format, ...){
	if (m_enabled && m_logTarget){
		va_list args;
		va_start(args, format);
			
		rString message = FormatString(format, args);
		m_logTarget->Info(message);
		
		va_end(args);
	}
}

void rLog::Error(const rString format, ...){
	if (m_enabled && m_logTarget){
		va_list args;
		va_start(args, format);
			
		rString message = FormatString(format, args);
		m_logTarget->Error(message);
		
		va_end(args);
	}
}

void rLog::Shutdown(){
	if (m_logTarget){
		m_logTarget->Shutdown();
		delete m_logTarget;
		m_logTarget = NULL;
	}
}

void rLog::SetEnabled(bool enabled){
	m_enabled = enabled;
}

bool rLog::Enabled(){
	return m_enabled;
}

//note this is a temporary implementation for now
rString rLog::FormatString(const rString format, va_list args){
	char buffer[2056];
	vsprintf (buffer, format.c_str(), args);
	
	return rString(buffer);
}
