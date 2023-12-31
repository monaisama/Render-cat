#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

uniform float offset;

out vec3 fsColor;

void main()
{
    fsColor = color;
    gl_Position = vec4(pos + offset, 1.f);
}