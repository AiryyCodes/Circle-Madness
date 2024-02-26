#include "player.h"
#include "bullet.h"
#include "camera.h"
#include "components/sprite_renderer.h"
#include "enemy.h"
#include "game.h"
#include "input.h"
#include "plane.h"
#include "score.h"
#include "time.h"
#include "math.h"
#include "sprite.h"
#include "window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/ext/quaternion_common.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>

float move_speed = 150.0f;
float lerp_speed = 7.5f;
float velocity_x;
float velocity_y;
float temp_velocity_x;
float temp_velocity_y;

float bullet_speed = 600.0f;
float bullet_radius = 2.0f;
Sprite bullet_sprite;

extern Camera camera;
extern Score score;

void Player::init()
{
    bullet_sprite = create_sprite("resources/textures/bullet.png");
}

void Player::update()
{
    if (is_button_just_down(GLFW_MOUSE_BUTTON_LEFT))
    {
        glm::vec2 mouse_position = glm::vec2{get_mouse_x(), get_mouse_y()};

        glm::vec3 world_pos = screen_to_world(mouse_position.x, mouse_position.y);

        double angle = std::atan2(world_pos.y - position.y, world_pos.x - position.x);

        Bullet* bullet = new Bullet(angle);
        bullet->add_component(new SpriteRenderer(bullet_sprite)); 
        bullet->get_position().x = (position.x + std::cos(angle) * bullet_radius * 25.0f);
        bullet->get_position().y = (position.y + std::sin(angle) * bullet_radius * 25.0f);
        bullet->get_rotation().y = angle;
        bullet->get_scale().x = 25.0f;
        bullet->get_scale().y = 25.0f;

        get_current_scene().add_node(bullet);
    }

    Plane* plane = get_current_scene().get_node<Plane>();

    float half_width = get_window_width() / 2.0f;
    float half_height = get_window_height() / 2.0f;

    get_position().x = clamp(get_position().x, -half_width + (get_scale().x / 2.0f), half_width - (get_scale().x / 2.0f));
    get_position().y = clamp(get_position().y, -half_height + (get_scale().y / 2.0f), half_height - (get_scale().y / 2.0f));

    std::vector<Bullet*> bullets = get_current_scene().get_nodes<Bullet>();
    std::vector<Enemy*> enemies = get_current_scene().get_nodes<Enemy>();
    for (Bullet* bullet : bullets)
    {
        for (auto* enemy : enemies)
        {
            if (bullet->is_inside(enemy))
            {
                get_current_scene().remove_node(enemy);

                get_current_scene().remove_node(bullet);
                score.increment();
            }
        }

        if (get_current_scene().has_node(bullet))
        {
            if (!bullet->is_inside(plane))
            {
                get_current_scene().remove_node(bullet);
                continue;
            }
            bullet->get_position() += glm::vec2(std::cos(bullet->get_angle()), std::sin(bullet->get_angle())) * bullet_speed * (float)get_delta_time();
        }
    }

    for (auto* enemy : enemies)
    {
        if (enemy->is_inside(this))
        {
            game_restart();
        }
    }
}

void Player::move()
{
    if (is_key_down(GLFW_KEY_W))
    {
        velocity_y = lerp(lerp_speed * get_delta_time(), velocity_y, move_speed);
        temp_velocity_y = velocity_y;
    }
    else if (is_key_down(GLFW_KEY_S))
    {
        velocity_y = lerp(lerp_speed * get_delta_time(), velocity_y, move_speed);
        temp_velocity_y = -velocity_y;
    }
    else
    {
        velocity_y = lerp(lerp_speed * get_delta_time(), velocity_y, 0.0f);
    }

    if (is_key_down(GLFW_KEY_A))
    {
        velocity_x = lerp(lerp_speed * get_delta_time(), velocity_x, move_speed);
        temp_velocity_x = velocity_x;
    }
    else if (is_key_down(GLFW_KEY_D))
    {
        velocity_x = lerp(lerp_speed * get_delta_time(), velocity_x, move_speed);
        temp_velocity_x = -velocity_x;
    }
    else
    {
        velocity_x = lerp(lerp_speed * get_delta_time(), velocity_x, 0.0f);
    }

    if (temp_velocity_y > 0.0f)
        get_position().y -= velocity_y * get_delta_time();
    else if (temp_velocity_y < 0.0f)
        get_position().y += velocity_y * get_delta_time();

    if (temp_velocity_x > 0.0f)
        get_position().x -= velocity_x * get_delta_time();
    else if (temp_velocity_x < 0.0f)
        get_position().x += velocity_x * get_delta_time();
}
