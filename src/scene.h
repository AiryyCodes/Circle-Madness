#pragma once

#include "node.h"

#include <algorithm>
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

    template<typename T>
    inline T* get_node()
    {
        for (auto* node : nodes)
        {
            if (typeid(*node) == typeid(T))
            {
                if (T* derived = dynamic_cast<T*>(node))
                    return derived;
            }
        }

        return nullptr;
    }

    template<typename T>
    inline std::vector<T*> get_nodes()
    {
        std::vector<T*> temp{};
        for (auto* node : nodes)
        {
            if (typeid(*node) == typeid(T))
            {
                T* derived = dynamic_cast<T*>(node);
                temp.push_back(derived);
            }
        }

        return temp;
    }

    template<typename T>
    inline bool has_node(T* node)
    {
        return std::find(nodes.begin(), nodes.end(), node) != nodes.end();
    }

    template<typename T>
    inline void remove_node(T* node)
    {
        nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
        delete node;
    }
    
private:
    std::vector<Node*> nodes;
};
