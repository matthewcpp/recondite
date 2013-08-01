#include "rAndroidLog.hpp"

void Debug(const rString& message){
	__android_log_print(ANDROID_LOG_DEBUG, "recondite", message.c_str());
}

void Warning(const rString& message){
	__android_log_print(ANDROID_LOG_WARN, "recondite", message.c_str());
}

void Trace(const rString& message){
	__android_log_print(ANDROID_LOG_VERBOSE, "recondite", message.c_str());
}

void Info(const rString& message){
	__android_log_print(ANDROID_LOG_INFO, "recondite", message.c_str());
}
