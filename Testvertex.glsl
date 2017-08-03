#version 330 core

in vec3	vertexPosition;
in vec3	vertexNormal;
in vec2	vertexUV;

out vec3	normal;
out vec2	uv;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main() {
	gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(vertexPosition, 1.0);

	normal = vertexNormal;
	uv = vertexUV;
}