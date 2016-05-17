#ifdef GLES2
	precision mediump float;
#endif

uniform vec4 fragColor;

void main() {
	gl_FragColor = fragColor;
}