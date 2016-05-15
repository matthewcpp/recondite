#ifdef GLES2
	precision mediump float;
#endif

varying vec2 v_texCoord;

uniform vec4 fragColor;
uniform sampler2D s_texture;
uniform vec2 v_uvOrigin;
uniform vec2 v_uvSize;

void main(){
	vec2 absoluteTexCoord = vec2(v_uvOrigin.x + (v_texCoord.x * v_uvSize.x), v_uvOrigin.y - ((1.0 - v_texCoord.y) * v_uvSize.y));
	
	vec4 texturedColor = texture2D( s_texture, absoluteTexCoord ) * fragColor;
	if (texturedColor.a < 0.1)
		discard;

	gl_FragColor = texturedColor;
}