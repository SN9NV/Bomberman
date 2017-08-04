#version 330 core

//in vec3	fragmentNormal;
in vec2	fragmentUV;

out vec4 colour;

//uniform sampler2D samplerUV;
//uniform int uIsCurves;

void main() {
//	if (uIsCurves > 0) {
//		colour = texture2D(samplerUV, fragmentUV);
//	} else {
//		colour = vec4(0.5 * normalize(fragmentNormal) + 0.5, 1.0);
//	}

//	colour = vec4(0.5 * normalize(fragmentNormal) + 0.5, 1.0);
	colour = vec4(fragmentUV, 0.0, 1.0);
//	colour = vec4(fragmentNormal.x * fragmentUV.x, fragmentNormal.y * fragmentUV.y, fragmentNormal.z, 1.0);
}