#include "game.h"
#include "input.h"
#include "shader.h"

#include <cstdio>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

unsigned int vbo;
unsigned int vao;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

Shader shader;

bool game_init()
{
    shader = create_shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");
    bind_shader(shader);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return true;
}

void game_update(double dt)
{
    if (is_key_down(GLFW_KEY_A))
    {
        printf("A is down\n");
    }

    if (is_key_just_down(GLFW_KEY_S))
    {
        printf("S was just pressed\n");
    }
}

void game_render()
{
    bind_shader(shader);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void game_cleanup()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader);
}
