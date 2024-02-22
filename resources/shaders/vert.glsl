#version 330 core

layout (location = 0) in vec3 l_pos;

void main()
{
    gl_Position = vec4(l_pos, 1.0);
}
