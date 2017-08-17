#version 330 core

const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 4;

layout(location = 0) in vec3	vertexPosition;
layout(location = 1) in vec3	vertexNormal;
layout(location = 2) in vec2	vertexUV;
layout(location = 3) in vec4	vertexJointIncides;
layout(location = 4) in vec4	vertexWeights;

out vec3	fragmentNormal;
out vec2	fragmentUV;
//out vec4	fragmentWeights;
out vec3	toLight;

uniform bool	isAnimated;
uniform mat4	jointTransforms[MAX_JOINTS];
uniform mat4	transformation;
uniform mat4	view;

const vec3 lightLocation = vec3(5.0, 5.0, 5.0);

void main() {
	mat4 skinMatrix;

	if (isAnimated) {
		skinMatrix =	vertexWeights.x * jointTransforms[int(vertexJointIncides.x)] +
						vertexWeights.y * jointTransforms[int(vertexJointIncides.y)] +
						vertexWeights.z * jointTransforms[int(vertexJointIncides.z)] +
						vertexWeights.w * jointTransforms[int(vertexJointIncides.w)];
	}

	vec4 position = /*skinMatrix **/ transformation * vec4(vertexPosition, 1.0);
	gl_Position = view * position;

	fragmentNormal = (skinMatrix * transformation * vec4(vertexNormal, 0.0)).xyz;
	fragmentUV = vertexUV;
//	fragmentWeights = vertexWeights;
	toLight = lightLocation - position.xyz;
}