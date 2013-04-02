#include "rOpenGLGraphicsDevice.hpp"

rOpenGLGraphicsDevice::rOpenGLGraphicsDevice()
{
	m_isInit = false;
}

bool rOpenGLGraphicsDevice::IsInit() const {
	return m_isInit;
}

void rOpenGLGraphicsDevice::Clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool rOpenGLGraphicsDevice::Init(){
    GLenum err = glewInit();
    
    if (err == GLEW_OK){
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_PERSPECTIVE_CORRECTION_HINT);

	glEnableClientState(GL_VERTEX_ARRAY);

	glColor4ub(255,255,255,255);

	glPointSize(4.0f);
	m_isInit = true;
    }
    
    return m_isInit;
}

void rOpenGLGraphicsDevice::DeleteShaderProgram(unsigned int shaderId){
	glDeleteProgram(shaderId);
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
	
	switch (viewport.ViewportType()){
		case rVIEWPORT_PERSP:
			SetPerspView(viewport);
			break;

		case rVIEWPORT_2D:
			Set2DView(viewport);
			break;
	};
}

void rOpenGLGraphicsDevice::CameraLookAt(rCamera* camera){
	rVector3 target = camera->Target();
	rVector3 position = camera->Position();
	rVector3 up = camera->Up();
    gluLookAt(position.x, position.y, position.z, target.x, target.y, target.z, up.x, up.y, up.z);
}

void rOpenGLGraphicsDevice::SetPerspView(rViewport& viewport){
    rRect rect = viewport.GetScreenRect();
	
    glViewport(rect.x, rect.y, rect.width, rect.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(rOGL_FOV_ANGLE, (GLfloat)rect.width / (GLfloat)rect.height, rOGL_Z_NEAR, rOGL_Z_FAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	rCamera* camera = viewport.Camera();

	if (camera)
		CameraLookAt(camera);
}

void rOpenGLGraphicsDevice::Set2DView(rViewport& viewport){
    rRect rect = viewport.GetScreenRect();
    glViewport(rect.x, rect.y, rect.width, rect.height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	gluOrtho2D(rect.Left(), rect.Right() , rect.Bottom() , rect.Top());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void rOpenGLGraphicsDevice::SetActiveMaterial(rMaterial* material){
}

void rOpenGLGraphicsDevice::DisableTextures(){
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

void rOpenGLGraphicsDevice::DrawWireBox(const rAlignedBox3& b, const rColor& color){
	DisableTextures();
	glColor4ub(color.Red() , color.Green() , color.Blue() , color.Alpha());
	SetBoxDrawPoints(b);
	glVertexPointer(3, GL_FLOAT , 0, &boxPoints[0]);
	glDrawElements(GL_LINES, wireBoxIndicies.size() , GL_UNSIGNED_SHORT , &wireBoxIndicies[0]);
}

void rOpenGLGraphicsDevice::DrawMesh(rVertex3Array& verticies, rVector2Array& texCoords, rIndexArray& indicies, rMaterial* material){

}

void rOpenGLGraphicsDevice::DrawLines3(const rVertex3Array& lines , const rColor& color){
	if (lines.size() > 0){
		DisableTextures();
		glColor4ub(color.Red() , color.Green() , color.Blue() , color.Alpha());
		glVertexPointer(3, GL_FLOAT , 0, &lines[0]);
		glDrawArrays(GL_LINES, 0 , lines.size());
	}
}

void rOpenGLGraphicsDevice::DrawPoints3(const rVertex3Array& points , const rColor& color){
	if (points.size() > 0){
		DisableTextures();
		glColor4ub(color.Red() , color.Green() , color.Blue() , color.Alpha());
		glVertexPointer(3, GL_FLOAT , 0, &points[0]);
		glDrawArrays(GL_POINTS, 0 , points.size());
	}
}

int rOpenGLGraphicsDevice::Unproject(const rVector3& v, rVector3& world){
    GLint viewport[4];
    GLdouble modelviewMatrix[16];
    GLdouble projectionMatrix[16];
    GLdouble objX , objY , objZ;

    glGetIntegerv(GL_VIEWPORT , viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelviewMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX , projectionMatrix);

    //need to translate window coordinates to opengl coordinates
    float adjustedY = viewport[3] - v.y;

	int result = gluUnProject(	v.x, adjustedY, v.z, 
								modelviewMatrix, projectionMatrix, viewport, 
								&objX, &objY, &objZ);
    
	if (result == GL_FALSE)
		return result;
	
	world.Set((float)objX , (float)objY, (float)objZ);
	
	return true;
}


unsigned int  rOpenGLGraphicsDevice::GenerateTextureID(){
	GLuint textureID;
	glGenTextures(1, &textureID);
	return textureID;
}

unsigned int rOpenGLGraphicsDevice::CreateTexture(int width, int height, int bpp , const unsigned char* data){
	GLuint textureID = GenerateTextureID();
	
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	GLenum format = (bpp == 3) ? GL_RGB : GL_RGBA;
	
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	
	return textureID;
}

void rOpenGLGraphicsDevice::UnregisterTexture(int textureID){
	GLuint texID(textureID);
	glDeleteTextures(1, &texID);
}

void rOpenGLGraphicsDevice::BindTexture2D(unsigned int textureID){
	glBindTexture(GL_TEXTURE_2D, textureID);
}