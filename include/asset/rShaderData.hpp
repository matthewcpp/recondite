#ifndef R_SHADER_DATA_HPP
#define R_SHADER_DATA_HPP

#include <fstream>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

class RECONDITE_API rShaderData{
public:
	rString VertexProgram() const;
	void SetVertexProgram(const rString& vertexProgram);

	rString FragmentProgram() const;
	void SetFragmentProgram(const rString& fragmentProgram);

	void Set(const rString& vertexProgram, const rString& fragmentProgram);
	void Clear();
	
private:
	rString m_vertexProgram;
	rString m_fragmentProgram;
};

#endif
