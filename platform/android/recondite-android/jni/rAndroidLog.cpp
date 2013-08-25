#include "rAndroidLog.hpp"

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
	__android_log_print(type, "recondite", "%s",message.c_str());
}
