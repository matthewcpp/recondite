#include "log/rLogFile.hpp"

rLogFile::rLogFile(const rString& path){
	m_file.open(path.c_str());
}

void rLogFile::Debug(const rString& message){
	DoLog("D: ", message);
}

void rLogFile::Warning(const rString& message){
	DoLog("W: ", message);
}

void rLogFile::Trace(const rString& message){
	DoLog("T: ", message);
}

void rLogFile::Info(const rString& message){
	DoLog("I: ", message);
}

void rLogFile::Error(const rString& message){
	DoLog("E: ", message);
}

void rLogFile::DoLog(const char* prefix, const rString& message){
	m_file << prefix << message << '\n';
}

void rLogFile::Shutdown(){
	m_file.close();
}

rLogFile::~rLogFile(){
	Shutdown();
}