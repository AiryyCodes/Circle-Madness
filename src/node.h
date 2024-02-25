#pragma once

#include "component.h"

#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <typeinfo>

class Node
{
public:
    Node() : position({0.0f, 0.0f}) {}
    Node(glm::vec2 arg_position) : position(arg_position) {}
    virtual ~Node() {}

    bool is_inside(Node* node);

    inline glm::vec2& get_position()
    {
        return position;
    }

    inline glm::vec2& get_rotation()
    {
        return rotation;
    }
    
    inline glm::vec2& get_scale()
    {
        return scale;
    }

    inline std::vector<Component*>& get_components()
    {
        return components;
    }

    inline glm::mat4 get_matrix()
    {
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, glm::vec3(position.x, position.y, 0.0f));
        matrix = glm::rotate(matrix, rotation.x, glm::vec3(-1.0f, 0.0f, 0.0f));
        matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.0f, 0.0f, 1.0f));
        matrix = glm::scale(matrix, glm::vec3(scale.x, scale.y, 1.0f));
        return matrix;
    }

    inline void add_component(Component* component)
    {
        components.push_back(component);
    }

    template<typename T>
    inline std::vector<T> get_components()
    {
        std::vector<T> temp{};
        for (auto* component : components)
        {
            if (typeid(*component) == typeid(T))
            {
                T* derived = dynamic_cast<T*>(component);
                temp.push_back(*derived);
            }
        }

        return temp;
    }

protected:
    glm::vec2 position;
    glm::vec2 rotation{0.0f, 0.0f};
    glm::vec2 scale{50.0f, 50.0f};

    std::vector<Component*> components;
};
