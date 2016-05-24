attribute vec4 recPosition;
attribute vec4 recNormal;

varying vec2 v_texCoord;

uniform mat4 recProjectionMatrix;
uniform mat4 recModelviewMatrix;

void main(){
	mat4 mvpMatrix = recProjectionMatrix * recModelviewMatrix;
	gl_Position = mvpMatrix * recPosition;
}