#version 330 core

in vec3 normal;
in vec2 uv;

out vec4 colour;

uniform sampler2D samplerUV;
uniform int uIsCurves;

void main() {
	if (uIsCurves > 0) {
		colour = texture2D(samplerUV, uv);
	} else {
		colour = vec4(0.5 * normalize(normal) + 0.5, 1.0);
	}
}