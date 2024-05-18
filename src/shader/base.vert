#version 320 es

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;

uniform mat4 proj;
uniform mat4 view;

out vec4 vertColor;

void main()
{
    gl_Position = proj * view * vec4(pos, 1.0);
    vertColor = color;
}

