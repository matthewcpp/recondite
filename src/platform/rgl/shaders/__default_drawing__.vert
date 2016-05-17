attribute vec4 recPosition;

uniform mat4 recMVPMatrix;

void main() {
  gl_Position = recMVPMatrix * recPosition;
}