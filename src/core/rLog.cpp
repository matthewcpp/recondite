#include "rLog.hpp"

rLogTarget* rLog::m_logTarget = NULL;
bool rLog::m_enabled = true;

void rLog::SetLogTarget(rLogTarget* target){
	m_logTarget = target;
}

void rLog::Debug(const rString& message){
	if (m_enabled && m_logTarget)
		m_logTarget->Debug(message);
}

void rLog::Warning(const rString& message){
	if (m_enabled && m_logTarget)
		m_logTarget->Warning(message);
}

void rLog::Trace(const rString& message){
	if (m_enabled && m_logTarget)
		m_logTarget->Trace(message);
}

void rLog::Info(const rString& message){
	if (m_enabled && m_logTarget)
		m_logTarget->Info(message);
}

void rLog::Error(const rString& message){
	if (m_enabled && m_logTarget)
		m_logTarget->Error(message);
}

void rLog::SetEnabled(bool enabled){
	m_enabled = enabled;
}

bool rLog::Enabled(){
	return m_enabled;
}
