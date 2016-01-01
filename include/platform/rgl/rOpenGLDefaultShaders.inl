//sprite shader
const char spriteVertexShader[] =

"attribute vec4 recPosition;"
"attribute vec2 recTexCoord;"
"varying vec2 v_texCoord;"
"uniform mat4 recMVPMatrix;"
"void main(){"
"	gl_Position = recMVPMatrix * recPosition;"
"	v_texCoord = recTexCoord;"
"}";

const char spriteFragmentShader[] =

"#ifdef GLES2\n"
"precision mediump float;\n"
"#endif\n"
"varying vec2 v_texCoord;"
"uniform vec4 fragColor;"
"uniform sampler2D s_texture;"
"void main(){"
"	vec4 texturedColor = texture2D( s_texture, v_texCoord ) * fragColor;"
"	if (texturedColor.a < 0.1)"
"		discard;"
"	gl_FragColor = texturedColor;"
"}";


//default shader for rendering a solid color
const char coloredVertexShader[] = 

"attribute vec4 recPosition;"
"uniform mat4 recMVPMatrix;"
"void main() {"
"  gl_Position = recMVPMatrix * recPosition;"
"}";

const char pointVertexShader[] = 

"attribute vec4 recPosition;"
"uniform float recPointSize;"
"uniform mat4 recMVPMatrix;"
"void main() {"
"  gl_PointSize = recPointSize;"
"  gl_Position = recMVPMatrix * recPosition;"
"}";

const char coloredFragmentShader[] = 
"#ifdef GLES2\n"
"precision mediump float;\n"
"#endif\n"
"uniform vec4 fragColor;"
"void main() {"
"  gl_FragColor = fragColor;"
"}";


const char modelVertexShader[] =

"attribute vec4 recPosition;"
"attribute vec4 recNormal;"
"attribute vec2 recTexCoord;"
"varying vec2 v_texCoord;"
"uniform mat4 recMVPMatrix;"
"void main(){"
"	gl_Position = recMVPMatrix * recPosition;"
"	v_texCoord = recTexCoord;"
"}";


//shader program for rendering geometry with texture coordinates

const char texturedVertexShader[] =

"attribute vec4 recPosition;"
"attribute vec2 recTexCoord;"
"varying vec2 v_texCoord;"
"uniform mat4 recMVPMatrix;"
"void main(){"
"	gl_Position = recMVPMatrix * recPosition;"
"	v_texCoord = recTexCoord;"
"}";

const char texturedFragmentShader[] =

"#ifdef GLES2\n"
"precision mediump float;\n"
"#endif\n"
"varying vec2 v_texCoord;"
"uniform vec4 fragColor;"
"uniform sampler2D s_texture;"
"void main(){"
"	vec4 texturedColor = texture2D( s_texture, v_texCoord ) * fragColor;"
"	if (texturedColor.a < 0.1)"
"		discard;"
"	gl_FragColor = texturedColor;"
"}";

//shader program for rendering geometry which has vertex colors
const char vertexColorVertexShader[] =

"attribute vec4 recPosition;"
"attribute vec4 recNormal;"
"attribute vec4 recVertexColor;"
""
"varying vec4 v_vertexColor;"
"uniform mat4 recMVPMatrix;"
""
"void main(){"
"	gl_Position = recMVPMatrix * recPosition;"
"	v_vertexColor = recVertexColor;"
"}";

const char vertexColorFragmentShader[] =

"#ifdef GLES2\n"
"precision mediump float;\n"
"#endif\n"
""
"varying vec4 v_vertexColor;"
""
"void main(){"
"	if (v_vertexColor.a < 0.1)"
"		discard;"
"	gl_FragColor = v_vertexColor;"
"}";