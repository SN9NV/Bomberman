#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

uniform mat4 modelview;
uniform mat4 projection;
uniform vec2 currTextureOff;
uniform vec2 nextTextureOff;
uniform float blend;
uniform float row;

out vec2 outCurrTextureOff;
out vec2 outNextTextureOff;
out float outBlend;
void main()
{
    gl_Position = projection * modelview * vec4(position.x, position.y, position.z, 1.0);
    vec2 txcoord = uv / row;
    outCurrTextureOff = currTextureOff + txcoord;
    outNextTextureOff = nextTextureOff + txcoord;
    outBlend = blend;
}