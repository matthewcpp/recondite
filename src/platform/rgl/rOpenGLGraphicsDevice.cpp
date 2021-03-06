#include "rgl/rOpenGLGraphicsDevice.hpp"

rOpenGLGraphicsDevice::rOpenGLGraphicsDevice(){
	m_isInit = false;
	m_nextRenderbufferId = 0;
	m_defaultFramebuffer = 0;
	m_activeRenderBufferId = 0;

	m_activeShaderProgram = -1;

	m_clearColor.Set(0, 0, 0, 255);
}

bool rOpenGLGraphicsDevice::IsInit() const {
	return m_isInit;
}

bool rOpenGLGraphicsDevice::Init(){
	rColor c(0, 0, 0, 255);
	SetClearColor(c);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_defaultFramebuffer);
	m_isInit = true;
    return m_isInit;
}

void rOpenGLGraphicsDevice::DeleteShaderProgram(unsigned int shaderId){
	glDeleteProgram(shaderId);
}

void rOpenGLGraphicsDevice::Clear(ClearFlags flags){
	GLbitfield clearFlags = 0;

	if ((flags & ClearFlags::Color) == ClearFlags::Color) {
		clearFlags |= GL_COLOR_BUFFER_BIT;
	}

	if ((flags & ClearFlags::Depth) == ClearFlags::Depth) {
		clearFlags |= GL_DEPTH_BUFFER_BIT;
	}

	glClear(clearFlags);
}

void rOpenGLGraphicsDevice::EnableDepthTesting(bool enable){
	if (enable){
		glEnable(GL_DEPTH_TEST);
	}
	else{
		glDisable(GL_DEPTH_TEST);
	}
}

void rOpenGLGraphicsDevice::SetDepthFunction(DepthFunction depthFunction) {
	switch (depthFunction)
	{
	case rGraphicsDevice::DepthFunction::LessEqual:
		glDepthFunc(GL_LEQUAL);
		break;
	default:
		glDepthFunc(GL_LESS);
		break;
	}
}

void rOpenGLGraphicsDevice::SetClearColor(const rColor& color){
	m_clearColor = color;

	glClearColor(float(color.red) / 255.0f, float(color.green) / 255.0f, float(color.blue) / 255.0f, float(color.alpha) / 255.0f);
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

		delete[] infoLog;
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
			Log::Error(m_lastError);

			delete[] infoLog;
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

void rOpenGLGraphicsDevice::SetViewport(int x, int y, int width, int height) {
	glViewport(x, y, width, height);
}

void rOpenGLGraphicsDevice::ActivateShader(unsigned int shaderId){
	m_activeShaderProgram = (GLint)shaderId;
	glUseProgram(m_activeShaderProgram);
}

void rOpenGLGraphicsDevice::SetSkinningData(const rMatrix4* matrices, size_t count) {
	GLint uniformHandle = glGetUniformLocation(m_activeShaderProgram, "recBoneMatrices");
	glUniformMatrix4fv(uniformHandle, count, GL_FALSE, (GLfloat*)matrices);
}

void rOpenGLGraphicsDevice::SetActiveMaterial(const rMaterial* material){
	GLint uniformHandle = glGetUniformLocation(m_activeShaderProgram, "fragColor");
	if (uniformHandle != -1){
		rColor diffuseColor = material->DiffuseColor();
		glUniform4f(uniformHandle, diffuseColor.red / 255.0f, diffuseColor.green / 255.0f, diffuseColor.blue / 255.0f, diffuseColor.alpha / 255.0f);
	}

	rTexture* diffuseTexture = material->DiffuseTexture();
	if (diffuseTexture){
		uniformHandle = glGetUniformLocation(m_activeShaderProgram, "s_texture");
		if (uniformHandle != -1){
			//set the texture as active
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseTexture->GraphicsDeviceID());
			glUniform1i(uniformHandle, 0);

			//pass the UV information into the shader
			uniformHandle = glGetUniformLocation(m_activeShaderProgram, "v_uvOrigin");
			const rVector2& uvOrigin = diffuseTexture->UVOrigin();
			glUniform2f(uniformHandle, uvOrigin.x, uvOrigin.y);

			uniformHandle = glGetUniformLocation(m_activeShaderProgram, "v_uvSize");
			const rVector2& uvSize = diffuseTexture->UVSize();
			glUniform2f(uniformHandle, uvSize.x, uvSize.y);
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

unsigned int rOpenGLGraphicsDevice::CreateGeometryBuffer(const recondite::GeometryData* geometryData) {
	GLuint bufferId;
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);

	size_t vertexDataSize = geometryData->VertexDataSize();
	size_t normalDataSize = geometryData->NormalDataSize();
	size_t texCoordDataSize = geometryData->TexCoordDataSize();
	size_t vertexBoneIndicesDataSize = geometryData->VertexBoneIndicesDataSize();
	size_t vertexBoneWeightDataSize = geometryData->VertexBoneWeightsDataSize();

	size_t bufferSize = vertexDataSize + normalDataSize + texCoordDataSize + vertexBoneIndicesDataSize + vertexBoneWeightDataSize;
	size_t offset = 0;

	glBufferData(GL_ARRAY_BUFFER, bufferSize, 0, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, offset, vertexDataSize, geometryData->VertexData());
	offset += vertexDataSize;

	if (geometryData->HasNormals()) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, normalDataSize, geometryData->NormalData());
		offset += normalDataSize;
	}

	if (geometryData->HasTexCoords()) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, texCoordDataSize, geometryData->TexCoordData());
		offset += texCoordDataSize;
	}

	if (geometryData->HasVertexBoneWeights()) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, vertexBoneIndicesDataSize, geometryData->VertexBoneIndicesData());
		offset += vertexBoneIndicesDataSize;

		glBufferSubData(GL_ARRAY_BUFFER, offset, vertexBoneWeightDataSize, geometryData->VertexBoneWeightData());
		offset += vertexBoneWeightDataSize;
	}

	return bufferId;
}

void rOpenGLGraphicsDevice::ActivateGeometryBuffer(const recondite::Geometry* geometry) {
	uint32_t offset = 0;
	GLuint vertexBufferId = geometry->GetBufferId();

	GLint gPositionLoc = glGetAttribLocation(m_activeShaderProgram, "recPosition");

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glEnableVertexAttribArray(gPositionLoc);
	glVertexAttribPointer(gPositionLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)offset);

	offset += geometry->GetVertexCount() * sizeof(rVector3);

	if (geometry->GetHasNormals()) {
		GLint gNormalLoc = glGetAttribLocation(m_activeShaderProgram, "recNormal");
		glEnableVertexAttribArray(gNormalLoc);	
		glVertexAttribPointer(gNormalLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)offset);

		offset += geometry->GetVertexCount() * sizeof(rVector3);
	}

	if (geometry->GetHasTexCoords()) {
		GLint gTexCoordLoc = glGetAttribLocation(m_activeShaderProgram, "recTexCoord");
		glEnableVertexAttribArray(gTexCoordLoc);
		glVertexAttribPointer(gTexCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)offset);

		offset += geometry->GetVertexCount() * sizeof(rVector2);
	}

	if (geometry->GetHasVertexBoneWeights()) {
		GLint gVertexBoneIndices = glGetAttribLocation(m_activeShaderProgram, "recBoneIndices");
		glEnableVertexAttribArray(gVertexBoneIndices);
		glVertexAttribIPointer(gVertexBoneIndices, 4, GL_INT, 0, (GLvoid *)offset);
		
		offset += geometry->GetVertexCount() * rMAX_BONE_WEIGHTS_PER_VERTEX * sizeof(uint32_t);

		GLint gVertexBoneWeights = glGetAttribLocation(m_activeShaderProgram, "recBoneWeights");
		glEnableVertexAttribArray(gVertexBoneWeights);
		glVertexAttribPointer(gVertexBoneWeights, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
	}
}

void rOpenGLGraphicsDevice::DeactivateGeometryBuffer(const recondite::Geometry* geometry) {
	GLuint gPositionLoc = glGetAttribLocation(m_activeShaderProgram, "recPosition");
	glDisableVertexAttribArray(gPositionLoc);

	if (geometry->GetHasNormals()) {
		GLuint gNormalLoc = glGetAttribLocation(m_activeShaderProgram, "recNormal");
		glDisableVertexAttribArray(gNormalLoc);
	}

	if (geometry->GetHasTexCoords()) {
		GLuint gTexCoordLoc = glGetAttribLocation(m_activeShaderProgram, "recTexCoord");
		glDisableVertexAttribArray(gTexCoordLoc);
	}

	if (geometry->GetHasVertexBoneWeights()) {
		GLuint gVertexBoneIndices = glGetAttribLocation(m_activeShaderProgram, "recBoneIndices");
		glDisableVertexAttribArray(gVertexBoneIndices);

		GLuint gVertexBoneWeights = glGetAttribLocation(m_activeShaderProgram, "recBoneWeights");
		glDisableVertexAttribArray(gVertexBoneWeights);
	}
}

unsigned int rOpenGLGraphicsDevice::CreateElementBuffer(const char* elementData, size_t elementDataSize){
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

void rOpenGLGraphicsDevice::RenderTriangleMesh(const recondite::Mesh* mesh, const rMatrix4& projection, const rMatrix4& modelview) {
	rMatrix4 normalMatrix = modelview;
	normalMatrix.Invert();
	normalMatrix.Transpose();

	GLuint gProjectionLoc = glGetUniformLocation(m_activeShaderProgram, "recProjectionMatrix");
	GLuint gModelviewLoc = glGetUniformLocation(m_activeShaderProgram, "recModelviewMatrix");
	GLuint gNormalMatLoc = glGetUniformLocation(m_activeShaderProgram, "recNormalMatrix");

	glUniformMatrix4fv(gProjectionLoc, 1, GL_FALSE, projection.m);
	glUniformMatrix4fv(gModelviewLoc, 1, GL_FALSE, modelview.m);
	glUniformMatrix4fv(gNormalMatLoc, 1, GL_FALSE, normalMatrix.m);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetElementBufferId());
	glDrawElements(GLGeometryType(mesh->GetGeometryType()), mesh->GetElementBufferCount(), GL_UNSIGNED_SHORT, 0);
}

void rOpenGLGraphicsDevice::RenderLineMesh(const recondite::Mesh* mesh, const rMatrix4& projection, const rMatrix4& modelview) {
	rMatrix4 mvpMatrix = projection * modelview;
	GLuint matrixLoc = glGetUniformLocation(m_activeShaderProgram, "recMVPMatrix");

	glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, mvpMatrix.m);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetElementBufferId());
	glDrawElements(GLGeometryType(mesh->GetGeometryType()), mesh->GetElementBufferCount(), GL_UNSIGNED_SHORT, 0);
}

void rOpenGLGraphicsDevice::RenderImmediate(const rImmediateBuffer& geometry, const rMatrix4& transform, rMaterial* material){
	if (material && geometry.VertexCount() > 0){
		size_t vertexElementSize = geometry.VertexSize();
		bool texCoords = geometry.HasTexCoords();

		GLsizei vertexStride = texCoords ? (vertexElementSize + 2) * sizeof (GLfloat) : 0;

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		SetActiveMaterial(material);

		GLuint gPositionLoc = glGetAttribLocation(m_activeShaderProgram, "recPosition");
		GLuint gMatrixLoc = glGetUniformLocation(m_activeShaderProgram, "recMVPMatrix");
		GLuint gTexCoordLoc = 0;
		
		glUniformMatrix4fv(gMatrixLoc, 1, GL_FALSE, transform.m);

		glVertexAttribPointer ( gPositionLoc, vertexElementSize, GL_FLOAT, GL_FALSE, vertexStride, geometry.VertexData() );
		glEnableVertexAttribArray ( gPositionLoc );

		if (texCoords){
			gTexCoordLoc = glGetAttribLocation(m_activeShaderProgram, "recTexCoord");
			glVertexAttribPointer ( gTexCoordLoc, 2, GL_FLOAT, GL_FALSE, vertexStride, geometry.VertexData() + (vertexElementSize * sizeof (GLfloat)));
			glEnableVertexAttribArray ( gTexCoordLoc );
		}
		glDrawElements ( GLGeometryType(geometry.GeometryType()), geometry.IndexCount(), GL_UNSIGNED_SHORT, geometry.IndexData() );

		glDisableVertexAttribArray ( gPositionLoc );

		if (texCoords)
			glDisableVertexAttribArray ( gTexCoordLoc );

	}
}

GLenum rOpenGLGraphicsDevice::GLGeometryType(rGeometryType type) const{
	switch (type){
	case rGeometryType::Lines:
		return GL_LINES;
	case rGeometryType::LineLoop:
		return GL_LINE_LOOP;
	case rGeometryType::Points:
		return GL_POINTS;
	default:
		return GL_TRIANGLES;
	}
}

unsigned int rOpenGLGraphicsDevice::CreateFramebuffer(int width, int height){
	rglRenderbuffer renderbuffer;
	renderbuffer.width = width;
	renderbuffer.height = height;
	
	glGenFramebuffers(1, &renderbuffer.framebufferId);
	glGenRenderbuffers(1, &renderbuffer.renderbufferId);
	glGenRenderbuffers(1, &renderbuffer.depthBufferId);

	glBindFramebuffer(GL_FRAMEBUFFER, renderbuffer.framebufferId);
	

	//TODO: For now just use render buffer object.  In future option for texture
	//todo: opengl es: GL_RGBA8_OES, GL_COLOR_ATTACHMENT0_OES? etc...
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer.renderbufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer.renderbufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer.depthBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.depthBufferId);

	unsigned int result = 0;
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status == GL_FRAMEBUFFER_COMPLETE) {
		unsigned int targetId = ++m_nextRenderbufferId;

		m_renderBuffers[targetId] = renderbuffer;
		result = targetId;
    }
	else{
		Log::Error("Error Creating Offscreen Renderbuffer: %d", status);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return result;
}

bool rOpenGLGraphicsDevice::DeleteFramebuffer(unsigned int id){
	if (m_renderBuffers.count(id)){
		rglRenderbuffer& renderbuffer = m_renderBuffers[id];

		glDeleteRenderbuffers(1, &renderbuffer.renderbufferId);
		glDeleteRenderbuffers(1, &renderbuffer.depthBufferId);
		glDeleteFramebuffers(1, &renderbuffer.framebufferId);
		
		if (m_activeRenderBufferId == id) {
			glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFramebuffer);
			m_activeRenderBufferId = 0;
		}

		m_renderBuffers.erase(id);
		
		return true;
	}
	else {
		return false;
	}
}

void rOpenGLGraphicsDevice::ReadActiveFramebuffer(const rRect& rect, unsigned char* buffer) {
	rglRenderbuffer& renderbuffer = m_renderBuffers[m_activeRenderBufferId];

	//TODO: Support GL_RGBA?
	glReadPixels(rect.x, rect.y, rect.width, rect.height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
}

bool rOpenGLGraphicsDevice::ActivateFramebuffer(unsigned int id) {
	if (m_renderBuffers.count(id)) {
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderBuffers[id].framebufferId);
		return true;
	}
	else {
		return false;
	}
}

unsigned int rOpenGLGraphicsDevice::GetActiveFramebufferId() {
	return m_activeRenderBufferId;
}

bool rOpenGLGraphicsDevice::GetFramebufferSize(unsigned int id, rSize& size) {
	if (m_renderBuffers.count(id)) {
		rglRenderbuffer& renderbuffer = m_renderBuffers[id];
		size.Set(renderbuffer.width, renderbuffer.height);
		return true;
	}
	else {
		return false;
	}
}