attribute vec4 recPosition;
attribute vec4 recNormal;
attribute vec2 recTexCoord;

varying vec2 v_texCoord;

uniform mat4 recMVPMatrix;

void main(){
	gl_Position = recMVPMatrix * recPosition;
	v_texCoord = recTexCoord;
}