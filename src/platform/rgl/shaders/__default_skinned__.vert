#define rMAX_BONE_TRANSFORMS 50

attribute vec4 recPosition;
attribute vec4 recNormal;
attribute vec2 recTexCoord;

attribute ivec4 recBoneIndices;
attribute vec4 recBoneWeights;

varying vec2 v_texCoord;

uniform mat4 recProjectionMatrix;
uniform mat4 recModelviewMatrix;
uniform mat4 recNormalMatrix;

uniform mat4 recBoneMatrices[rMAX_BONE_TRANSFORMS];

varying vec3 normalInterp;
varying vec3 vertPos;

void main(){
	mat4 boneMatrix = recBoneMatrices[recBoneIndices[0]] * recBoneWeights[0];
	boneMatrix += recBoneMatrices[recBoneIndices[1]] * recBoneWeights[1];
	boneMatrix += recBoneMatrices[recBoneIndices[2]] * recBoneWeights[2];
	boneMatrix += recBoneMatrices[recBoneIndices[3]] * recBoneWeights[3];

	mat4 mvpMatrix = recProjectionMatrix * recModelviewMatrix * boneMatrix;
	gl_Position = mvpMatrix * recPosition;

	vec4 vertPos4 = recModelviewMatrix * vec4(recPosition.xyz, 1.0);
	vertPos = vec3(vertPos4) / vertPos4.w;
	normalInterp = vec3(recNormalMatrix * vec4(recNormal.xyz, 0.0));

	v_texCoord = recTexCoord;
}