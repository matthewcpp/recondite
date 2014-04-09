#include "data/rShaderData.hpp"

rShaderData::rShaderData(){
	Clear();
}

rShaderData::rShaderData(const rString& path){
	LoadFromPath(path);
}

rShaderData::rShaderData(std::istream& vertexStream, std::istream& fragmentStream){
	LoadFromStreams(vertexStream, fragmentStream);
}

void rShaderData::Clear(){
	m_vertexProgram.clear();
	m_fragmentProgram.clear();
	
	m_error = rCONTENT_ERROR_NONE;
}

rContentError rShaderData::LoadFromPath(const rString& path){
	rString vertexPath = path + ".vertex";
	rString fragmentPath = path + "fragment";
	
	SetPath(path);
	
	return LoadFromPaths(vertexPath, fragmentPath);
}

rContentError rShaderData::LoadFromPaths(const rString& vertexPath, const rString& fragmentPath){
	std::ifstream vertexStream(vertexPath.c_str());
	std::ifstream fragmentStream(fragmentPath.c_str());
	
	if (vertexStream || fragmentStream)
		m_error = LoadFromStreams(vertexStream, fragmentStream);
	else
		m_error = rCONTENT_ERROR_FILE_NOT_FOUND;
	
	vertexStream.close();
	fragmentStream.close();
	
	return m_error;
}

void rShaderData::ReadStreamToString(std::istream& stream, rString& str){
	stream.seekg(0, std::ios::end);
	str.resize(stream.tellg());
	stream.seekg(0, std::ios::beg);
	stream.read(&str[0], str.size());
}

rContentError rShaderData::LoadFromStreams(std::istream& vertexStream, std::istream& fragmentStream){
	ReadStreamToString(vertexStream, m_vertexProgram);
	ReadStreamToString(fragmentStream, m_fragmentProgram);
	
	m_error =  rCONTENT_ERROR_NONE;
	return m_error;
}

rContentError rShaderData::SetShaderData(const rString& vertexProgram, const rString& fragmentProgram){
	Clear();
	
	m_vertexProgram = vertexProgram;
	m_fragmentProgram = fragmentProgram;
	
	m_error = rCONTENT_ERROR_NONE;
	return m_error;
}

rContentError rShaderData::WriteToPath(const rString& path) const{
	rString vertexPath = path + ".vertex";
	rString fragmentPath = path + "fragment";
	return WriteToPaths(vertexPath, fragmentPath);
}

rContentError rShaderData::WriteToPaths(const rString& vertexPath, const rString& fragmentPath) const{
	rContentError error = rCONTENT_ERROR_NONE;
	std::ofstream vertexStream(vertexPath.c_str());
	std::ofstream fragmentStream(fragmentPath.c_str());
	
	if (vertexStream && fragmentStream)
		error = WriteToStreams(vertexStream, fragmentStream);
	else
		error = rCONTENT_ERROR_FILE_NOT_WRITABLE;
	
	vertexStream.close();
	fragmentStream.close();
	
	return error;
}

rContentError rShaderData::WriteToStreams(std::ostream& vertexStream, std::ostream& fragmentStream) const{
	vertexStream << m_vertexProgram;
	fragmentStream << m_fragmentProgram;
	
	return rCONTENT_ERROR_NONE;
}

rString rShaderData::GetVertexProgram() const{
	return m_vertexProgram;
}

rString rShaderData::GetFragmentProgram() const{
	return m_fragmentProgram;
}

rContentError rShaderData::GetError() const{
	return m_error;
}

rString rShaderData::GetPath() const{
	return m_path;
}

void rShaderData::SetPath(const rString& path){
	m_path = path;
}
