//default shader for rendering a solid color
const char coloredVertexShader[] = 

"attribute vec4 recPosition;"
"uniform mat4 recMVPMatrix;"
"void main() {"
"  gl_Position = recMVPMatrix * recPosition;"
"}";

static const char coloredFragmentShader[] = 
"precision mediump float;"
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

const char texturedFragmentShader[] =

"precision mediump float;"
"varying vec2 v_texCoord;"
"uniform sampler2D s_texture;"
"void main(){"
"	gl_FragColor = texture2D( s_texture, v_texCoord );"
"}";
