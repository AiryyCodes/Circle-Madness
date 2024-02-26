#pragma once

class Node;

class Component
{
public:
    virtual ~Component() {}

    inline void set_parent(Node* parent)
    {
        this->parent = parent;
    }

    inline Node* get_parent()
    {
        return parent;
    }

protected:
    Node* parent;
};

#include "node.h"
