#version 330 core

layout(location = 0) in vec3	vertexPosition;
layout(location = 1) in vec3	vertexNormal;
layout(location = 2) in vec2	vertexUV;

out vec3	fragmentNormal;
out vec2	fragmentUV;
out vec3	toLight;

uniform mat4 transformation;
uniform mat4 view;

const vec3 lightLocation = { 5.0, 5.0, 5.0 };

void main() {
	gl_Position = view * transformation * vec4(vertexPosition, 1.0);

	fragmentNormal = vertexNormal;
	fragmentUV = vertexUV;
	toLight = lightLocation - vertexPosition;
}