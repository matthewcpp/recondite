#ifdef GLES2
	precision mediump float;
#endif

uniform vec4 fragColor;
uniform sampler2D s_texture;
uniform vec2 v_uvOrigin;
uniform vec2 v_uvSize;

varying vec2 v_texCoord;

varying vec3 normalInterp;
varying vec3 vertPos;

const vec3 lightPos = vec3(1.0,1.0,1.0);
const vec3 ambientColor = vec3(0.2, 0.2, 0.2);
vec3 diffuseColor = fragColor.xyz;
const vec3 specColor = vec3(1.0, 1.0, 1.0);

void main() {
	vec2 absoluteTexCoord = vec2(v_uvOrigin.x + (v_texCoord.x * v_uvSize.x), v_uvOrigin.y - ((1.0 - v_texCoord.y) * v_uvSize.y));
	
	vec4 texturedColor = texture2D( s_texture, absoluteTexCoord );
	if (texturedColor.a < 0.1)
		discard;

	vec3 normal = normalize(normalInterp);
	vec3 lightDir = normalize(lightPos - vertPos);

	float lambertian = max(dot(lightDir,normal), 0.0);
	float specular = 0.0;

	vec3 viewDir = normalize(-vertPos);

	// this is blinn phong
	vec3 halfDir = normalize(lightDir + viewDir);
	float specAngle = max(dot(halfDir, normal), 0.0);
	specular = pow(specAngle, 16.0);

	vec4 shadedColor = vec4(ambientColor + lambertian * diffuseColor + specular * specColor, 1.0);

	gl_FragColor = shadedColor * texturedColor;

}
