#version 330 core

in	vec2	fragmentPosition;
in	vec4	fragmentColour;
in	vec2	fragmentUV;

out	vec4	colour;

uniform float		time;
uniform sampler2D	mySampler;

void main() {
	vec4 myTexture = texture(mySampler, fragmentUV);

	vec4	newColour;
	newColour[0] = fragmentColour[0] * 0.5f * (cos(fragmentPosition[0] * 4.0f + time) + 1.0f);
	newColour[1] = fragmentColour[1] * 0.5f * (cos(fragmentPosition[0] * 4.0f + time + 2.094395102f) + 1.0f);
	newColour[2] = fragmentColour[2] * 0.5f * (cos(fragmentPosition[0] * 4.0f + time + 4.188790205f) + 1.0f);

	colour = myTexture * newColour;
}
