#include "asset/rShader.hpp"

rShader::rShader(const rString& name, unsigned int programId)
{
	m_programId = programId;
	m_name = name;
}

rString rShader::Name() const{
	return m_name;
}

unsigned int rShader::ProgramId() const{
	return m_programId;
}