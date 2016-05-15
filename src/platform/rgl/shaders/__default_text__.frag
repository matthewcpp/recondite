#ifdef GLES2
	precision mediump float;\n
#endif

varying vec2 v_texCoord;

uniform vec4 fragColor;
uniform sampler2D s_texture;

void main(){
	vec4 texturedColor = texture2D( s_texture, v_texCoord ) * fragColor;
	
	if (texturedColor.a < 0.1)
		discard;
		
	gl_FragColor = texturedColor;
}