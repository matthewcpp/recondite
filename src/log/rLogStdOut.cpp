#include "log/rLogStdOut.hpp"

void rLogStdOut::Debug(const rString& message){
	std::cout << message.c_str() << std::endl;
}

void rLogStdOut::Warning(const rString& message){
	std::cout << message.c_str() << std::endl;
}

void rLogStdOut::Trace(const rString& message){
	std::cout << message.c_str() << std::endl;
}

void rLogStdOut::Info(const rString& message){
	std::cout << message.c_str() << std::endl;
}

void rLogStdOut::Error(const rString& message){
	std::cout << message.c_str() << std::endl;
}