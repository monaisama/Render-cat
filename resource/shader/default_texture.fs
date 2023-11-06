#version 330 core

in vec2 texCorrd;
uniform sampler2D tex0;
uniform sampler2D tex1;

out vec4 color;

void main()
{
    color = mix(texture(tex0, texCorrd), texture(tex1, texCorrd), 0.3);
}