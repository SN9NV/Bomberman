#version 330 core

in vec3 colour;
in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec2 fragmentUV;

out vec4 out_colour;

uniform sampler2D modelTexture;

void main() {
	out_colour = texture(modelTexture, fragmentUV);
}