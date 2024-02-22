#pragma once

typedef unsigned int Shader;

Shader create_shader(const char* vert_path, const char* frag_path);
void bind_shader(Shader &shader);
void unbind_shader();
