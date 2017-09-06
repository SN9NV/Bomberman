#version 330 core

in vec2	fragmentUV;

out vec4 colour;

uniform sampler2D samplerUV;

void main() {

	colour = texture(samplerUV, fragmentUV);
}