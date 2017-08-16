#version 330 core

in vec2 outCurrTextureOff;
in vec2 outNextTextureOff;
in float outBlend;

out vec4 colour;

uniform sampler2D particalTexture;

void main() {
	colour = mix(texture(particalTexture, outCurrTextureOff), texture(particalTexture, outNextTextureOff), outBlend);
}