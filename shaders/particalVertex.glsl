#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in mat4 modelview;
layout (location = 6) in vec2 currTextureOff;
layout (location = 7) in vec2 nextTextureOff;
layout (location = 8) in float blend;

uniform mat4 projection;
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