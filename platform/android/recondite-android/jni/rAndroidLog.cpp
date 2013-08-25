#include "rAndroidLog.hpp"

rAndroidLog::rAndroidLog(){
	m_logTag = NULL;
	SetLogTag("recondite");
}

rAndroidLog::~rAndroidLog(){
	if (m_logTag)
		delete[] m_logTag;
}

void rAndroidLog::SetLogTag(const rString& tag){
	if (tag.length() > 0){
		if (m_logTag)
			delete[] m_logTag;

		m_logTag = new char[tag.length() + 1];
		strcpy(m_logTag, tag.c_str());
	}
}

void rAndroidLog::Debug(const rString& message){
	DoLog(ANDROID_LOG_DEBUG, message.c_str());
}

void rAndroidLog::Warning(const rString& message){
	DoLog(ANDROID_LOG_WARN, message.c_str());
}

void rAndroidLog::Trace(const rString& message){
	DoLog(ANDROID_LOG_VERBOSE, message.c_str());
}

void rAndroidLog::Info(const rString& message){
	DoLog(ANDROID_LOG_INFO, message.c_str());
}

void rAndroidLog::Error(const rString& message){
	DoLog(ANDROID_LOG_ERROR, message.c_str());
}

void rAndroidLog::DoLog( int type, const rString& message){
	__android_log_print(type, m_logTag, "%s",message.c_str());
}
