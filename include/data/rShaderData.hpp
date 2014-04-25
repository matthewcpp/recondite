#ifndef R_SHADER_DATA_HPP
#define R_SHADER_DATA_HPP

#include <fstream>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

class RECONDITE_API rShaderData{
public:
	rShaderData();
	rShaderData(const rString& path);
	rShaderData(std::istream& vertexStream, std::istream& fragmentStream);
	
	void Clear();
	
	rContentError LoadFromPath(const rString& path);
	rContentError LoadFromPaths(const rString& vertexPath, const rString& fragmentPath);
	rContentError LoadFromStreams(std::istream& vertexStream, std::istream& fragmentStream);
	rContentError SetShaderData(const rString& vertexProgram, const rString& fragmentProgram);
	
	rContentError WriteToPath(const rString& path) const;
	rContentError WriteToPaths(const rString& vertexPath, const rString& fragmentPath) const;
	rContentError WriteToStreams(std::ostream& vertexStream, std::ostream& fragmentStream) const;
public:
	rString GetVertexProgram() const;
	rString GetFragmentProgram() const;
	
	rContentError GetError() const;
	
	rString GetPath() const;
	void SetPath(const rString& path);
private:
	//todo move to utils
	static void ReadStreamToString(std::istream& stream, rString& str);
	
private:
	rString m_vertexProgram;
	rString m_fragmentProgram;
	rContentError m_error;
	rString m_path;
};

#endif
