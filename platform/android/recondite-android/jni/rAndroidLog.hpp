#ifndef R_ANDROIDLOG_HPP
#define R_ANDROIDLOG_HPP

#include <android/log.h>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rLogTarget.hpp"

class rAndroidLog : public rLogTarget{
public:
	rAndroidLog();
	~rAndroidLog();

	void Debug(const rString& message);
	void Warning(const rString& message);
	void Trace(const rString& message);
	void Info(const rString& message);
	void Error(const rString& message);

	void SetLogTag(const rString& tag);

private:
	void DoLog( int type, const rString& message);

	char* m_logTag;
};

#endif
