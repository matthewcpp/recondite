#include "rOpenGLGraphicsDevice.hpp"

rOpenGLGraphicsDevice::rOpenGLGraphicsDevice()
{
	m_isInit = false;
}

bool rOpenGLGraphicsDevice::IsInit(){
	return m_isInit;
}

void rOpenGLGraphicsDevice::Clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void rOpenGLGraphicsDevice::Init(){
	GLenum err = glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_PERSPECTIVE_CORRECTION_HINT);

	glEnableClientState(GL_VERTEX_ARRAY);

	glColor4ub(255,255,255,255);

	glPointSize(2.0f);
	m_isInit = true;
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
	glViewport(	viewport.m_windowPos.x,viewport.m_windowPos.y,
				viewport.m_windowSize.width, viewport.m_windowSize.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(rOGL_FOV_ANGLE, (GLfloat)viewport.m_windowSize.width / (GLfloat)viewport.m_windowSize.height, rOGL_Z_NEAR, rOGL_Z_FAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	rCamera* camera = viewport.Camera();

	if (camera)
		CameraLookAt(camera);
}

void rOpenGLGraphicsDevice::Set2DView(rViewport& viewport){
	glViewport(	viewport.m_windowPos.x,viewport.m_windowPos.y,
				viewport.m_windowSize.width, viewport.m_windowSize.height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	rRectangle2 r = viewport.Get2DScreenRect();

	gluOrtho2D(r.Left(), r.Right() ,r.Bottom() ,r.Top());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void rOpenGLGraphicsDevice::SetActiveMaterial(rMaterial* material){
}

void rOpenGLGraphicsDevice::DrawWireBox(const rAlignedBox3& b, const rColor& color){
	glColor4ub(color.Red() , color.Green() , color.Blue() , color.Alpha());
	SetBoxDrawPoints(b);
	glVertexPointer(3, GL_FLOAT , 0, &boxPoints[0]);
	glDrawElements(GL_LINES, wireBoxIndicies.size() , GL_UNSIGNED_SHORT , &wireBoxIndicies[0]);
}

void rOpenGLGraphicsDevice::DrawMesh(rVertex3Array& verticies, rVector2Array& texCoords, rIndexArray& indicies, rMaterial* material){
	rColor color = material->Color();
	glColor4ub(color.Red() , color.Green() , color.Blue() , color.Alpha());
	
	rTexture2D* texture = material->DiffuseTex();
	if (texture){
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D, texture->GraphicsDeviceID());
		glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);
	}
	else{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}
	
	SetActiveMaterial(material);
	glVertexPointer(3, GL_FLOAT , 0, &verticies[0]);
	glDrawElements(GL_TRIANGLES, indicies.size() , GL_UNSIGNED_SHORT , &indicies[0]);
}

void rOpenGLGraphicsDevice::DrawLines3(const rVertex3Array& lines , const rColor& color){
	glColor4ub(color.Red() , color.Green() , color.Blue() , color.Alpha());
	glVertexPointer(3, GL_FLOAT , 0, &lines[0]);
	glDrawArrays(GL_LINES, 0 , lines.size());
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