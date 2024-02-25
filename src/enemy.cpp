#include "enemy.h"
#include "components/sprite_renderer.h"
#include "game.h"
#include "plane.h"
#include "player.h"
#include "scene.h"
#include "sprite.h"
#include "time.h"
#include "window.h"

#include <glm/fwd.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <random>

float speed = 110.0f;

float random_float(float min, float max)
{
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(generator);
}

void Enemy::init()
{
    Sprite sprite = create_sprite("resources/textures/enemy.png");
    add_component(new SpriteRenderer(sprite));

    Plane* plane = get_current_scene().get_node<Plane>();
    while (is_inside(plane))
    {
        position.x = random_float(-get_window_width(), get_window_width());
        position.y = random_float(-get_window_height(), get_window_height());
    }
}

void Enemy::move()
{
    Scene scene = get_current_scene();
    Player* player = scene.get_node<Player>();

    glm::vec2 destination = position - player->get_position();
    destination = glm::normalize(destination);

    if (destination.x > 0.0f || destination.y > 0.0f || destination.x < 0.0f || destination.y < 0.0f)
        position -= destination * speed * (float)get_delta_time();
}
