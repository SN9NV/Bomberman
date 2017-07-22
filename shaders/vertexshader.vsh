#version 330 core

in	vec2	vertexPosition;
in	vec4	vertexColour;

out	vec4	fragmentColour;

void main() {
	gl_Position.xy = vertexPosition;
	gl_Position.z = 0.0f;
	gl_Position.w = 1.0f;

	fragmentColour = vertexColour;
}
