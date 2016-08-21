#ifdef GLES2
	precision mediump float;
#endif

uniform vec4 fragColor;

varying vec3 normalInterp;
varying vec3 vertPos;

const vec3 lightPos = vec3(1.0,1.0,1.0);
const vec3 ambientColor = vec3(0.0, 0.0, 0.0);
vec3 diffuseColor = fragColor.xyz;
const vec3 specColor = vec3(1.0, 1.0, 1.0);

void main() {

  vec3 normal = normalize(normalInterp);
  vec3 lightDir = normalize(lightPos - vertPos);

  float lambertian = max(dot(lightDir,normal), 0.0);
  float specular = 0.0;

  if(lambertian > 0.0) {

    vec3 viewDir = normalize(-vertPos);

    // this is blinn phong
    vec3 halfDir = normalize(lightDir + viewDir);
    float specAngle = max(dot(halfDir, normal), 0.0);
    specular = pow(specAngle, 16.0);

  gl_FragColor = vec4(ambientColor +
                      lambertian * diffuseColor +
                      specular * specColor, 1.0);
					  }
}
