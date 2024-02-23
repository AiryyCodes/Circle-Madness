#pragma once

#include <glm/fwd.hpp>
#include <string>

typedef unsigned int Shader;

Shader create_shader(const char* vert_path, const char* frag_path);
void bind_shader(Shader &shader);
void unbind_shader();

void set_uniform(unsigned int shader, std::string location, glm::vec2& value);
void set_uniform(unsigned int shader, std::string location, glm::mat4& value);
