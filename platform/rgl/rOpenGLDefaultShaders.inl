const char texturedVertexShader[] =
"attribute vec4 a_position;"
"attribute vec2 a_texCoord;"
"varying vec2 v_texCoord;"
"void main()"
"{"
"	gl_Position = a_position;"
"	v_texCoord = a_texCoord;"
"}";

const char texturedFragmentShader[] =
"precision mediump float;"
"varying vec2 v_texCoord;"
"uniform sampler2D s_texture;"
"void main()"
"{"
"	gl_FragColor = texture2D( s_texture, v_texCoord );"
"}";
