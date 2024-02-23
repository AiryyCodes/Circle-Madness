#version 330 core

out vec4 frag_color;

in vec3 out_color;
in vec2 out_tex_coord;

uniform sampler2D uni_texture;

void main()
{
    frag_color = texture(uni_texture, out_tex_coord);
}
