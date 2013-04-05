//default shader for rendering a solid color
const char coloredVertexShader[] = 

"attribute vec4 vPosition;"
"varying vec4 fragColor;"
"void main() {"
"  gl_Position = vPosition;"
"}";

static const char coloredFragmentShader[] = 
"precision mediump float;"
"varying vec4 fragColor;"
"void main() {"
"  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);"
"}";

//default shader for rendering a textured triangle

const char texturedVertexShader[] =

"attribute vec4 a_position;"
"attribute vec2 a_texCoord;"
"varying vec2 v_texCoord;"
"void main(){"
"	gl_Position = a_position;"
"	v_texCoord = a_texCoord;"
"}";

const char texturedFragmentShader[] =

"precision mediump float;"
"varying vec2 v_texCoord;"
"uniform sampler2D s_texture;"
"void main(){"
"	gl_FragColor = texture2D( s_texture, v_texCoord );"
"}";
