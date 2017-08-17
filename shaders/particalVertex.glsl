#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in mat4 modelview;
/*layout (location = 2) in vec4 modelview1;
layout (location = 3) in vec4 modelview2;
layout (location = 4) in vec4 modelview3;
layout (location = 5) in vec4 modelview4;*/
layout (location = 6) in vec2 currTextureOff;
layout (location = 7) in vec2 nextTextureOff;
layout (location = 8) in float blend;

//uniform mat4 modelview;
uniform mat4 projection;
//uniform vec2 currTextureOff;
//uniform vec2 nextTextureOff;
//uniform float blend;
uniform float row;

out vec2 outCurrTextureOff;
out vec2 outNextTextureOff;
out float outBlend;
void main()
{
    /*mat4 modelview;
    modelview[0] = modelview1;
    modelview[1] = modelview2;
    modelview[2] = modelview3;
    modelview[3] = modelview4;*/
    gl_Position = projection * modelview * vec4(position.x, position.y, position.z, 1.0);
    vec2 txcoord = uv / row;
    outCurrTextureOff = currTextureOff + txcoord;
    outNextTextureOff = nextTextureOff + txcoord;
    outBlend = blend;
}