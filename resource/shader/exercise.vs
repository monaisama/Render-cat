#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

uniform mat4 matrix;

out vec3 fColor;

void main()
{
    gl_Position = matrix * vec4(pos, 1.f);
    fColor = color;
}