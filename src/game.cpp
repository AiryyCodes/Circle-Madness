#include "game.h"
#include "bullet.h"
#include "camera.h"
#include "enemy.h"
#include "plane.h"
#include "shader.h"
#include "sprite.h"
#include "scene.h"
#include "time.h"
#include "window.h"
#include "player.h"

#include "components/sprite_renderer.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>

Shader shader;
Sprite sprite;
Scene current_scene;
Player player;
Plane plane;
Camera camera;

Sprite plane_sprite;

float enemy_time_passed;

bool game_init()
{
    shader = create_shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");

    sprite = create_sprite("resources/textures/player.png");

    plane_sprite = create_sprite("resources/textures/placeholder.png");
    //plane.add_component(new SpriteRenderer(plane_sprite));
    plane.get_scale().x = get_window_width();
    plane.get_scale().y = get_window_height();
    plane.get_position().x = -get_window_width() / 2.0f;
    plane.get_position().y = -get_window_height() / 2.0f;
    current_scene.add_node(&plane);

    camera.get_position().x = -(get_window_width() / 2.0f);
    camera.get_position().y = -(get_window_height() / 2.0f);

    player.add_component(new SpriteRenderer(sprite));
    current_scene.add_node(&player);
    current_scene.add_node(&camera);

    for (Node* node : current_scene.get_nodes())
    {
        for (SpriteRenderer renderer : node->get_components<SpriteRenderer>())
        {
            renderer.init();
        }
    }

    player.init();

    return true;
}

void game_update()
{
    plane.get_scale().x = get_window_width();
    plane.get_scale().y = get_window_height();

    player.update();
    player.move();

    enemy_time_passed += get_delta_time();
    if (enemy_time_passed > 2.5f)
    {
        Enemy* enemy = new Enemy();
        enemy->init();
        current_scene.add_node(enemy);
        enemy_time_passed = 0.0f;
    }

    std::vector<Enemy*> enemies = current_scene.get_nodes<Enemy>();
    for (auto* enemy : enemies)
    {
        enemy->move();
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

void game_restart()
{
    Player* player = current_scene.get_node<Player>();
    player->get_position().x = 0.0f;
    player->get_position().y = 0.0f;
    
    for (Bullet* bullet : current_scene.get_nodes<Bullet>())
    {
        current_scene.remove_node(bullet);
    }

    for (Enemy* enemy : current_scene.get_nodes<Enemy>())
    {
        current_scene.remove_node(enemy);
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

        for (Component* component : node->get_components())
        {
            delete component;
        }

        delete node;
    }
    glDeleteProgram(shader);
}

Scene& get_current_scene()
{
    return current_scene;
}
