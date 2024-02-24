#pragma once

#include "node.h"
#include <glm/fwd.hpp>

class Bullet : public Node
{
public:
    Bullet(double angle) :
        angle(angle) {}

    inline double get_angle()
    {
        return angle;
    }

private:
    glm::vec2 direction;
    glm::vec2 velocity;

    double angle;
};
