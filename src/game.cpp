#include "game.h"
#include "bullet.h"
#include "camera.h"
#include "components/font_renderer.h"
#include "enemy.h"
#include "math.h"
#include "plane.h"
#include "score.h"
#include "shader.h"
#include "sprite.h"
#include "scene.h"
#include "time.h"
#include "window.h"
#include "player.h"

#include "components/sprite_renderer.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>

Shader shader;
Shader text_shader;
Sprite sprite;
Scene current_scene;
Player player;
Plane plane;
Camera camera;
Score score;

float enemy_time_passed;
float difficulty = 2.0f;

bool game_init()
{
    shader = create_shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");
    text_shader = create_shader("resources/shaders/text_vert.glsl", "resources/shaders/text_frag.glsl");

    sprite = create_sprite("resources/textures/player.png");

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

    score.add_component(new FontRenderer("Score: 0", glm::vec3(0.25f, 0.25f, 0.25f), "resources/fonts/Antonio-Bold.ttf", 1.0));
    score.get_position().y = 48.0f;
    score.get_position().x = 4.0f;
    current_scene.add_node(&score);

    for (Node* node : current_scene.get_nodes())
    {
        for (SpriteRenderer renderer : node->get_components<SpriteRenderer>())
        {
            renderer.init();
        }

        for (FontRenderer renderer : node->get_components<FontRenderer>())
        {
            renderer.init(text_shader);
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

    difficulty = clamp(difficulty, 0.35f, 2.0f);

    enemy_time_passed += get_delta_time();
    if (enemy_time_passed > difficulty)
    {
        Enemy* enemy = new Enemy();
        enemy->get_position().x = get_window_width() / 2.0f - enemy->get_scale().x;
        enemy->get_position().y = get_window_height() / 2.0f - enemy->get_scale().y;
        enemy->init();
        current_scene.add_node(enemy);
        enemy_time_passed = 0.0f;
        difficulty -= 0.05f;
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

    score.get_component<FontRenderer>()->render(text_shader);
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

    score.reset();
    difficulty = 2.0f;
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
    glDeleteProgram(text_shader);
}

Scene& get_current_scene()
{
    return current_scene;
}
