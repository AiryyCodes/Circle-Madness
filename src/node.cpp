#include "node.h"

bool Node::is_inside(Node* node)
{
    return position.x < node->get_position().x + node->get_scale().x &&
            position.x + scale.x > node->get_position().x &&
            position.y < node->get_position().y + node->get_scale().y &&
            position.y + scale.y > node->get_position().y;
}
