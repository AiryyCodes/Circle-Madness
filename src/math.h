#pragma once

#include <glm/fwd.hpp>

template<typename T>
T clamp(T value, T min, T max);

float lerp(float value, float start, float end);

glm::vec3 screen_to_world(double mouse_x, double mouse_y);
