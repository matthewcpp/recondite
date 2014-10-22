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

//default shader for rendering a textured triangle

const char texturedVertexShader[] =

"attribute vec4 recPosition;"
"attribute vec2 recTexCoord;"
"varying vec2 v_texCoord;"
"uniform mat4 recMVPMatrix;"
"void main(){"
"	gl_Position = recMVPMatrix * recPosition;"
"	v_texCoord = recTexCoord;"
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
