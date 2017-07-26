#version 330 core

in	vec2	fragmentPosition;
in	vec4	fragmentColour;
in	vec2	fragmentUV;

out	vec4	colour;

uniform sampler2D	mySampler;

void main() {
	vec4 myTexture = texture(mySampler, fragmentUV);

	colour = myTexture * fragmentColour;
}
