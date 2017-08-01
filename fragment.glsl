#version 330 core

in vec3 fragmentPosition;
in vec2 fragmentUV;
in vec3 fragmentNormal;

out vec4 colour;

uniform sampler2D modelTexture;

void main() {
	colour =  texture(modelTexture, fragmentUV);
}