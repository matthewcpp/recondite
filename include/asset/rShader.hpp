#ifndef R_SHADER_HPP
#define R_SHADER_HPP

#include <map>

#include "rBuild.hpp"
#include "rString.hpp"

class RECONDITE_API rShader{
public:
	rShader(const rString& name, unsigned int programId);
	
	unsigned int ProgramId() const;
	rString Name() const;
	
private:
	unsigned int m_programId;
	rString m_name;
};

#endif
