#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec3 fragmentPosition;
out vec2 fragmentUV;
out vec3 fragmentNormal;

uniform mat4 transformation;
uniform mat4 view;

void main() {
	gl_Position = view * transformation * vec4(vertexPosition, 1.0);

	fragmentPosition = vertexPosition;
	fragmentUV = vertexUV;
	fragmentNormal = vertexNormal;
}