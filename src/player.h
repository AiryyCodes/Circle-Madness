#pragma once

#include "node.h"
#include <glm/fwd.hpp>

class Player : public Node
{
public:
    void init();
    void update();
    void move();

private:
    glm::vec2 velocity;
};
