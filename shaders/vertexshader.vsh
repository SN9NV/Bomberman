#version 330 core

in	vec2	vertexPosition;
in	vec4	vertexColour;
in	vec2	vertexUV;

out	vec4	fragmentColour;
out	vec2	fragmentPosition;
out	vec2	fragmentUV;

void main() {
	gl_Position.xy = vertexPosition;
	gl_Position.z = 0.0f;
	gl_Position.w = 1.0f;

	fragmentColour = vertexColour;
	fragmentPosition = vertexPosition;
	fragmentUV = vec2(vertexUV.x, 1.0f - vertexUV.y);
}
