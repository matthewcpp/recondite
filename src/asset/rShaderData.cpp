#include "asset/rShaderData.hpp"


rString rShaderData::VertexProgram() const{
	return m_vertexProgram;
}

void rShaderData::SetVertexProgram(const rString& vertexProgram){
	m_vertexProgram = vertexProgram;
}

rString rShaderData::FragmentProgram() const{
	return m_fragmentProgram;
}

void rShaderData::SetFragmentProgram(const rString& fragmentProgram){
	m_fragmentProgram = fragmentProgram;
}

void rShaderData::Set(const rString& vertexProgram, const rString& fragmentProgram){
	SetVertexProgram(vertexProgram);
	SetFragmentProgram(fragmentProgram);
}

void rShaderData::Clear(){
	m_vertexProgram.clear();
	m_fragmentProgram.clear();
}