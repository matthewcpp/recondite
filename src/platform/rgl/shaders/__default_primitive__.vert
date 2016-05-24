attribute vec4 recPosition;
attribute vec4 recNormal;

uniform mat4 recProjectionMatrix;
uniform mat4 recModelviewMatrix;
uniform mat4 recNormalMatrix;

varying vec3 normalInterp;
varying vec3 vertPos;

void main(){
	mat4 mvpMatrix = recProjectionMatrix * recModelviewMatrix;
	gl_Position = mvpMatrix * recPosition;

	vec4 vertPos4 = recModelviewMatrix * vec4(recPosition.xyz, 1.0);
	vertPos = vec3(vertPos4) / vertPos4.w;
	normalInterp = vec3(recNormalMatrix * vec4(recNormal.xyz, 0.0));
}