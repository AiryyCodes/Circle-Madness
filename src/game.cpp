#include "game.h"
#include "camera.h"
#include "input.h"
#include "shader.h"
#include "sprite.h"
#include "scene.h"
#include "components/sprite_renderer.h"
#include "window.h"

#include <cstdio>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>

Shader shader;
Sprite sprite;
Scene current_scene;
Node player_node;
Camera camera;

bool game_init()
{
    shader = create_shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");

    sprite = create_sprite("resources/textures/Player.png");

    camera.get_position().x = -(get_window_width() / 2);
    camera.get_position().y = -(get_window_height() / 2);

    player_node.add_component(new SpriteRenderer(sprite));
    current_scene.add_node(&player_node);
    current_scene.add_node(&camera);

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
    glViewport(0, 0, get_window_width(), get_window_height());

    if (is_key_down(GLFW_KEY_A))
    {
        camera.get_position().x += 100.0f;
    }
    else if (is_key_down(GLFW_KEY_D))
    {
        camera.get_position().x -= 100.0f;
    }

    if (is_key_just_down(GLFW_KEY_S))
    {
        printf("S was just pressed\n");
    }
}

void game_render()
{
    bind_shader(shader);

    glm::mat4 proj_matrix = camera.get_proj_matrix();
    set_uniform(shader, "projection", proj_matrix);
        
    glm::mat4 view_matrix = camera.get_view_matrix();
    set_uniform(shader, "view", view_matrix);

    for (Node* node : current_scene.get_nodes())
    {
        glm::mat4 transform_matrix = node->get_matrix();
        set_uniform(shader, "transform", transform_matrix);

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
