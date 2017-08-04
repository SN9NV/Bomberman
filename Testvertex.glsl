#version 330 core

in vec3	vertexPosition;
//in vec3	vertexNormal;
in vec2	vertexUV;
//
//out vec3	fragmentNormal;
out vec2	fragmentUV;

//uniform mat4 transformation;
uniform mat4 view;

void main() {
	gl_Position = view * /*transformation **/ vec4(vertexPosition, 1.0);

//	fragmentNormal = vertexNormal;
	fragmentUV = vertexUV;
}