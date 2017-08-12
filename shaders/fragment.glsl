#version 330 core

in vec3	fragmentNormal;
in vec2	fragmentUV;
in vec4	fragmentWeights;
in vec3	toLight;

out vec4 colour;

uniform bool		showWeights;
uniform bool		isInvisible;
uniform sampler2D	samplerUV;

void main() {
	if (showWeights) {
		colour = vec4(fragmentWeights.xyz, 1);
	} else {
		vec3 unitNormal = normalize(fragmentNormal);
		vec3 unitToLight = normalize(toLight);

		float normalBrightness = dot(unitNormal, unitToLight);
		float brightness = max(normalBrightness, 0.1);
		vec4 diffuse = vec4(vec3(brightness), 1.0);

		colour = diffuse * texture(samplerUV, fragmentUV);
	}

	if (isInvisible) {
		colour *= vec4(1, 1, 1, 0.5); ///> Makes the model half invisable
	}
}