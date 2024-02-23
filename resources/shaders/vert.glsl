#version 330 core

layout (location = 0) in vec3 l_position;
layout (location = 1) in vec3 l_color;
layout (location = 2) in vec2 l_tex_coord;

out vec3 out_color;
out vec2 out_tex_coord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(l_position, 1.0);
    out_color = l_color;
    out_tex_coord = l_tex_coord;
}
