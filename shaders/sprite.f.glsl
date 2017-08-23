#version 330 core

in vec2 texpos;
out vec4 color;

uniform sampler2D tex;
uniform vec3 textColor;

void main()
{
    color = texture(tex, texpos);
}