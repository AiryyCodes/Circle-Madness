#include "shader.h"

#include <cstdio>
#include <glad/gl.h>
#include <fstream>
#include <iterator>
#include <string>
#include <glm/gtc/type_ptr.hpp>

void compile_shader(unsigned int shader, const char* path);
std::string read_file(const char* file_path);

Shader create_shader(const char *vert_path, const char *frag_path)
{
    unsigned int vert_id = glCreateShader(GL_VERTEX_SHADER);
    unsigned int frag_id = glCreateShader(GL_FRAGMENT_SHADER);

    compile_shader(vert_id, vert_path);
    compile_shader(frag_id, frag_path);

    unsigned int program_id = glCreateProgram();

    glAttachShader(program_id, vert_id);
    glAttachShader(program_id, frag_id);
    glLinkProgram(program_id);

    int success;
    char log[1024];
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program_id, 1024, NULL, log);
        printf("Failed to link shader program.\n%s", log);
    }

    glUseProgram(program_id);

    glDeleteShader(vert_id);
    glDeleteShader(frag_id);

    return program_id;
}

void bind_shader(Shader &shader)
{
    glUseProgram(shader);
}

void unbind_shader()

{
    glUseProgram(0);
}

void compile_shader(unsigned int shader, const char* path)
{
    std::string contents = read_file(path);
    const char* src = contents.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    
    int success;
    char log[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, log);
        printf("Failed to compile shader.\n%s", log);
    }
}

std::string read_file(const char* file_path)
{
    std::ifstream in(file_path);
    return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

void set_uniform(unsigned int shader, std::string location, glm::vec2& value)
{
    glUniform2fv(glGetUniformLocation(shader, location.c_str()), 1, glm::value_ptr(value));
}

void set_uniform(unsigned int shader, std::string location, glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(shader, location.c_str()), 1, glm::value_ptr(value));
}

void set_uniform(unsigned int shader, std::string location, glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(shader, location.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
