#include "game.h"
#include "input.h"
#include "shader.h"
#include "sprite.h"
#include "scene.h"
#include "components/sprite_renderer.h"

#include <cstdio>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>

Shader shader;
Sprite sprite;
Scene current_scene;
Node player_node;

bool game_init()
{
    shader = create_shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");

    sprite = create_sprite("resources/textures/Player.png");

    player_node.add_component(new SpriteRenderer(sprite));
    current_scene.add_node(&player_node);

    for (Node* node : current_scene.get_nodes())
    {
        for (SpriteRenderer renderer : node->get_components<SpriteRenderer>())
        {
            renderer.init();
        }
    }

    return true;
}

void game_update(double dt)
{
    // glViewport(0, 0, 1280, 720);

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
    for (Node* node : current_scene.get_nodes())
    {
        glm::mat4 matrix = node->get_matrix();
        set_uniform(shader, "transform", matrix);
        std::vector<SpriteRenderer> renderers = node->get_components<SpriteRenderer>();
        for (SpriteRenderer renderer : renderers)
        {
            renderer.render();
        }
    }
}

void game_cleanup()
{
    for (Node* node : current_scene.get_nodes())
    {
        for (SpriteRenderer renderer : node->get_components<SpriteRenderer>())
        {
            renderer.cleanup();
        }

        delete node;
    }
    glDeleteProgram(shader);
}
