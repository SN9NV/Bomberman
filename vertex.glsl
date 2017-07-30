#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexUV;

out vec3 colour;
out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec2 fragmentUV;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main() {
	gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(vertexPosition, 1.0);

	fragmentPosition = vertexPosition;
	fragmentNormal = vertexNormal;
	fragmentUV = vertexUV;

	colour = vec3(vertexPosition.x + 0.5, 0.0, vertexPosition.y + 0.5);
}