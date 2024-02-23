#pragma once

#include "node.h"

#include <vector>

class Scene
{
public:
    inline void add_node(Node* node)
    {
        nodes.push_back(node);
    }

    inline std::vector<Node*>& get_nodes()
    {
        return nodes;
    }

private:
    std::vector<Node*> nodes;
};
