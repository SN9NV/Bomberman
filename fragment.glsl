#version 330 core

in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec2 fragmentUV;

out vec4 out_colour;

uniform sampler2D modelTexture;

void main() {
	vec2 uv = vec2(fragmentNormal.x * fragmentUV.x, fragmentNormal.y * fragmentUV.y);
	out_colour =  texture(modelTexture, uv);
}