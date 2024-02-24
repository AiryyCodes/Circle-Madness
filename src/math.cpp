#include "math.h"
#include "camera.h"
#include "window.h"
#include <glm/fwd.hpp>

extern Camera camera;

template<typename T>
T clamp(T value, T min, T max)
{
    const T clamped = value < min ? min : value;
    return clamped > max ? max : clamped;
}

float lerp(float value, float start, float end)
{
    value = clamp(value, 0.0f, 1.0f);
    return start + (end - start) * value;
}

glm::vec3 screen_to_world(double mouse_x, double mouse_y)
{
    double x = 2.0 * mouse_x / get_window_width() - 1;
    double y = 2.0 * mouse_y / get_window_height() - 1;

    glm::vec4 screen_pos = glm::vec4(x, -y, -1.0, 1.0);

    glm::mat4 project_view = camera.get_proj_matrix() * camera.get_view_matrix();
    glm::mat4 view_proj_inverse = glm::inverse(project_view);

    glm::vec4 world_pos4 = view_proj_inverse * screen_pos;
    return glm::vec3(world_pos4);
}
