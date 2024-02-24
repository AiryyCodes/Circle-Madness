#pragma once

#include "node.h"

class Plane : public Node
{
public:
    bool is_inside(Node* node);
};
