#include "rOpenGLGraphicsDevice.hpp"

rOpenGLGraphicsDevice::rOpenGLGraphicsDevice()
{
	m_isInit = false;
}

bool rOpenGLGraphicsDevice::IsInit() const {
	return m_isInit;
}

bool rOpenGLGraphicsDevice::Init(){
	SetClearColor(0,0,0,1);
	
	glEnable(GL_DEPTH_TEST);

	m_isInit = true;
    return m_isInit;
}

void rOpenGLGraphicsDevice::DeleteShaderProgram(unsigned int shaderId){
	glDeleteProgram(shaderId);
}

void rOpenGLGraphicsDevice::Clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void rOpenGLGraphicsDevice::EnableDepthTesting(bool enable){
	if (enable){
		glEnable(GL_DEPTH_TEST);
	}
	else{
		glDisable(GL_DEPTH_TEST);
	}
}

void rOpenGLGraphicsDevice::SetClearColor(const rColor& color){
	SetClearColor(float(color.red) / 255.0f, float(color.green) / 255.0f, float(color.blue) / 255.0f, float(color.alpha) / 255.0f);
}

void rOpenGLGraphicsDevice::SetClearColor(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
}

unsigned int rOpenGLGraphicsDevice::CreateShaderProgram(const rString& vertex, const rString& fragment){
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;


    vertexShader = CompileShader(GL_VERTEX_SHADER, vertex.c_str());

    if (!vertexShader)
	    return 0;

    fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragment.c_str());

    if (!fragmentShader){
	    glDeleteShader(vertexShader);
	    return 0;
    }

    programObject = glCreateProgram();

    if (!programObject)
	    return 0;

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    glLinkProgram(programObject);
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    if (!linked){
	GLint infoLen = 0;
	glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

	if (infoLen > 1){
	     char* infoLog = new char[infoLen];

	     glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
	     m_lastError.assign(infoLog, infoLen);         

	     delete [] infoLog;
	}

	glDeleteProgram(programObject);
	return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_lastError.clear();
    return programObject;
}

GLuint rOpenGLGraphicsDevice::CompileShader(GLenum type, const char* program){
    GLuint shader;
    GLint compiled;

    shader = glCreateShader(type);

    if (!shader)
	    return 0;

    glShaderSource(shader, 1, &program, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	
    if (!compiled){
      GLint infoLen = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

      if (infoLen > 1){
	 char* infoLog = new char[infoLen];

	 glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
	 m_lastError.assign(infoLog, infoLen);
	 rLog::Error(m_lastError);

	 delete [] infoLog;
      }

      glDeleteShader(shader);
      return 0;
    }

    m_lastError.clear();
    return shader;
}

void rOpenGLGraphicsDevice::Uninit(){
	m_isInit = false;
}

void rOpenGLGraphicsDevice::SetViewport(int x , int y, int width, int height) {
	glViewport(x, y, width, height);
}

void rOpenGLGraphicsDevice::SetActiveMaterial(rMaterial* material){
	int textureIndex = 0;
	GLint programId = material->Shader()->ProgramId();
	rArrayString paramNames;
	rMaterialParameter parameter;
	material->GetParameterNames(paramNames);
	
	glUseProgram(programId);
	
	for (size_t i = 0; i < paramNames.size(); i++){
		material->GetParameter(paramNames[i], parameter);
		GLint uniformHandle = glGetUniformLocation ( programId, paramNames[i].c_str() );
		
		switch (parameter.m_type){
			case rMATERIAL_PARAMETER_COLOR:{
				rColor color;
				parameter.GetColor(color);
				glUniform4f(uniformHandle, color.red / 255.0f, color.green / 255.0f, color.blue / 255.0f , color.alpha / 255.0f);
			}
			break;

			case rMATERIAL_PARAMETER_TEXTURE2D:{
				rTexture2D* texture = parameter.GetTexture();
				glActiveTexture ( GL_TEXTURE0 + textureIndex);
				glBindTexture ( GL_TEXTURE_2D, texture->GraphicsDeviceID() );
				glUniform1i ( uniformHandle, textureIndex );
				textureIndex ++;

				if (texture->Bpp() > 3){
					glEnable (GL_BLEND);
					glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}
				else{
					glDisable(GL_BLEND);
				}

			}
			break;

			case rMATERIAL_PARAMETER_FLOAT:{
				float f = parameter.GetFloat();
				glUniform1f(uniformHandle, f);
			}
			break;
		}


	}
}

unsigned int rOpenGLGraphicsDevice::CreateArrayBuffer(const char* data, size_t dataSize){
	GLuint bufferId;
	glGenBuffers(1, &bufferId);
	
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	
	return bufferId;
}

unsigned int rOpenGLGraphicsDevice::CreateElementBuffer(const unsigned short* elementData, size_t elementDataSize){
	GLuint bufferId;
	glGenBuffers(1, &bufferId);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementDataSize, elementData, GL_STATIC_DRAW);
	
	return bufferId;
}

void rOpenGLGraphicsDevice::DeleteBuffer(unsigned int bufferId){
	glDeleteBuffers(1, &bufferId);
}

unsigned int rOpenGLGraphicsDevice::CreateTexture(int width, int height, int bpp , const unsigned char* data){
	unsigned char* oglTexData = ReflectTexture(width, height, bpp, data);

	GLenum format = (bpp == 3) ? GL_RGB : GL_RGBA;
	GLuint textureID;
	
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, oglTexData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	delete[] oglTexData;

	return textureID;
}

unsigned char* rOpenGLGraphicsDevice::ReflectTexture(int width, int height, int bpp , const unsigned char* data){
	unsigned char* oglData = new unsigned char[width * height * bpp];
	unsigned int rowSize = width * bpp;

	int srcRow = height - 1;
	int destRow = 0;

	while (srcRow >= 0){
		memcpy(oglData + (destRow * rowSize), data + (srcRow * rowSize), rowSize);

		srcRow--;
		destRow++;
	}

	return oglData;
}

void rOpenGLGraphicsDevice::UnregisterTexture(int textureID){
	GLuint texID(textureID);
	glDeleteTextures(1, &texID);
}

GLsizei rOpenGLGraphicsDevice::GetVertexStrideForGeometry(size_t vertexSize, bool texCoords, bool normals) const{
	if (texCoords && normals)
		return (vertexSize + 5) * sizeof(GLfloat);
	else if (texCoords && !normals)
		return (vertexSize + 2) * sizeof(GLfloat);
	else return 0;
}

GLsizei rOpenGLGraphicsDevice::GetTexCoordStrideForGeometry(size_t vertexSize, bool normals) const{
	if (normals)
		return (vertexSize + 5) * sizeof (GLfloat);
	else
		return (vertexSize + 2) * sizeof (GLfloat);
}

void rOpenGLGraphicsDevice::RenderGeometry(rGeometry* geometry, const rMatrix4& transform, const rString& elementBufferName, rMaterial* material){
	rElementBuffer elementBuffer;
	
	if (geometry && material && geometry->GetElementBuffer(elementBufferName, elementBuffer)){
		size_t vertexElementSize = geometry->VertexElementSize();
		GLsizei vertexStride = GetVertexStrideForGeometry(3, geometry->HasTexCoords(), geometry->HasNormals());
		SetActiveMaterial(material);
		
		GLint programId = material->Shader()->ProgramId();
		GLuint vertexBuffer = geometry->VertexBufferId();
		GLuint gPositionLoc = glGetAttribLocation ( programId, "recPosition" );
		GLuint gMatrixLoc = glGetUniformLocation ( programId, "recMVPMatrix" );
		
		glUniformMatrix4fv(gMatrixLoc, 1, GL_FALSE, transform.m);
		
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer ( gPositionLoc, vertexElementSize, GL_FLOAT, GL_FALSE, vertexStride, 0 );
		glEnableVertexAttribArray ( gPositionLoc );
		
		if (geometry->HasTexCoords()){
			GLuint gTexCoordLoc = glGetAttribLocation ( programId, "recTexCoord" );
			GLsizei texCoordStride = GetTexCoordStrideForGeometry(vertexElementSize, geometry->HasNormals());
			GLuint firstTexCoordOffset = texCoordStride - (2 * sizeof (GLfloat));
			glVertexAttribPointer ( gTexCoordLoc, 2, GL_FLOAT, GL_FALSE, texCoordStride, (void*)firstTexCoordOffset);
			glEnableVertexAttribArray ( gTexCoordLoc );
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer.BufferId());

		glDrawElements ( GLGeometryType(elementBuffer.GeometryType()), elementBuffer.Size(), GL_UNSIGNED_SHORT, 0 );

		glDisableVertexAttribArray ( gPositionLoc );
	}
}

void rOpenGLGraphicsDevice::RenderImmediate(rImmediateBuffer& geometry, const rMatrix4& transform, rMaterial* material){
	if (material){
		size_t vertexElementSize = geometry.VertexSize();
		bool texCoords = geometry.HasTexCoords();

		GLsizei vertexStride = vertexElementSize * sizeof (GLfloat);
		if (texCoords)
			vertexStride += 2 * sizeof (GLfloat);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		SetActiveMaterial(material);

		GLint programId = material->Shader()->ProgramId();
		GLuint gPositionLoc = glGetAttribLocation ( programId, "recPosition" );
		GLuint gMatrixLoc = glGetUniformLocation ( programId, "recMVPMatrix" );
		
		glUniformMatrix4fv(gMatrixLoc, 1, GL_FALSE, transform.m);

		glVertexAttribPointer ( gPositionLoc, vertexElementSize, GL_FLOAT, GL_FALSE, vertexStride, geometry.VertexData() );
		glEnableVertexAttribArray ( gPositionLoc );

		if (texCoords){
			GLuint gTexCoordLoc = glGetAttribLocation ( programId, "recTexCoord" );
			glVertexAttribPointer ( gTexCoordLoc, 2, GL_FLOAT, GL_FALSE, vertexStride, geometry.VertexData() + (vertexElementSize * sizeof (GLfloat)));
			glEnableVertexAttribArray ( gTexCoordLoc );
		}
		glDrawElements ( GLGeometryType(geometry.GeometryType()), geometry.IndexCount(), GL_UNSIGNED_SHORT, geometry.IndexData() );

		glDisableVertexAttribArray ( gPositionLoc );

	}
}

GLenum rOpenGLGraphicsDevice::GLGeometryType(rGeometryType type) const{
	switch (type){
	case rGEOMETRY_LINES:
		return GL_LINES;
	case rGEOMETRY_LINE_LOOP:
		return GL_LINE_LOOP;
	case rGEOMETRY_POINTS:
		return GL_POINTS;
	default:
		return GL_TRIANGLES;
	}
}

GLenum rOpenGLGraphicsDevice::GLDataType(rDataType type) const{
	return GL_FLOAT;
}