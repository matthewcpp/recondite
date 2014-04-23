#ifndef R_LOGFILE_HPP
#define R_LOGFILE_HPP

#include <fstream>

#include "rDefs.hpp"

#include "log/rLogTarget.hpp"
#include "rLogChain.hpp"

class RECONDITE_API rLogFile : public rLogTarget{
public:
	rLogFile(const rString& path);
	
	
	virtual void Debug(const rString& message);
	virtual void Warning(const rString& message);
	virtual void Trace(const rString& message);
	virtual void Info(const rString& message);
	virtual void Error(const rString& message);
	
private:

	void DoLog(const char* prefix, const rString& message);
	
private:
	std::ofstream m_file;
};

#endif