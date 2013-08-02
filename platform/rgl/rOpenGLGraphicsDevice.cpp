#include "rOpenGLGraphicsDevice.hpp"

rOpenGLGraphicsDevice::rOpenGLGraphicsDevice()
{
	m_isInit = false;
}

bool rOpenGLGraphicsDevice::IsInit() const {
	return m_isInit;
}

bool rOpenGLGraphicsDevice::Init(){
	m_isInit = true;
    return m_isInit;
}

void rOpenGLGraphicsDevice::DeleteShaderProgram(unsigned int shaderId){
	glDeleteProgram(shaderId);
}

void rOpenGLGraphicsDevice::Clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void rOpenGLGraphicsDevice::SetActiveViewport(rViewport& viewport){
	
}

void rOpenGLGraphicsDevice::SetActiveMaterial(rMaterial* material){
	int textureIndex;
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
			}
			break;
		}
	}
}

unsigned int rOpenGLGraphicsDevice::CreateVertexBuffer(const float* vertexData, size_t vertexDataSize){
	GLuint bufferId;
	glGenBuffers(1, &bufferId);
	
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	
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
	GLenum format = (bpp == 3) ? GL_RGB : GL_RGBA;
	GLuint textureID;
	
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	return textureID;
}

void rOpenGLGraphicsDevice::UnregisterTexture(int textureID){
	GLuint texID(textureID);
	glDeleteTextures(1, &texID);
}