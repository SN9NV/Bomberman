#version 330 core

in vec3	fragmentNormal;
in vec2	fragmentUV;
in vec3	toLight;

out vec4 colour;

uniform sampler2D samplerUV;

void main() {
	vec3 unitNormal = normalize(fragmentNormal);
	vec3 unitToLight = normalize(toLight);

	float normalBrightness = dot(unitNormal, unitToLight);
	float brightness = max(normalBrightness, 0.1);
	vec4 diffuse = vec4(vec3(brightness), 1.0);

	colour = diffuse * texture(samplerUV, fragmentUV);
	colour = vec4(1.0, 1.0, 1.0, 1.0);
}