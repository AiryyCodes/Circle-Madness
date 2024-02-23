#pragma once

class Node;

class Component
{
public:
    virtual ~Component() {}

    inline Node* get_parent()
    {
        return parent;
    }

private:
    Node* parent;
};
