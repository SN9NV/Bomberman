#version 330 core

const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 4;

layout(location = 0) in vec3	vertexPosition;
layout(location = 1) in vec3	vertexNormal;
layout(location = 2) in vec2	vertexUV;
layout(location = 3) in ivec4	vertexJointIncides;
layout(location = 4) in vec4	vertexWeights;

out vec3	fragmentNormal;
out vec2	fragmentUV;
out vec3	toLight;

uniform mat4	jointTransforms[MAX_JOINTS];
uniform mat4	transformation;
uniform mat4	view;

const vec3 lightLocation = vec3(5.0, 5.0, 5.0);

void main() {
	vec4	totalLocalPos = vec4(0.0);
	vec4	totalNormal = vec4(0.0);

	for (int i = 0; i < MAX_WEIGHTS; i++) {
		mat4	jointTransform = jointTransforms[vertexJointIncides[i]];
		vec4	posePosition = jointTransform * vec4(vertexPosition, 1.0);
		totalLocalPos += posePosition * vertexWeights[i];

		vec4	worldNormal = jointTransform * vec4(vertexNormal, 0.0);
		totalNormal += worldNormal * vertexWeights[i];
	}

	gl_Position = view * transformation * totalLocalPos;

	fragmentNormal = (transformation * totalNormal).xyz;
	fragmentUV = vertexUV;
	toLight = lightLocation - (transformation * totalLocalPos).xyz;
}