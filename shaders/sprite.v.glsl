#version 330 core

layout(location = 0) in vec4 coord;
out vec2 texpos;

uniform mat4 project;

void main(void) {
  gl_Position = project * vec4(coord.xy, 0, 1);
  texpos = coord.zw;
}
