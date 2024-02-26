#pragma once

#include "node.h"
#include "window.h"

#include <cstdio>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

class Camera : public Node
{
public:
    inline glm::mat4 get_proj_matrix()
    {
        width = get_window_width();
        height = get_window_height();
        glm::mat4 matrix(1.0f);
        matrix = glm::ortho(0.0f, width, height, 0.0f);
        return matrix;
    }

    inline glm::mat4 get_view_matrix()
    {
        glm::mat4 matrix(1.0f);
           
        glm::vec3 new_pos = glm::vec3(position.x, position.y, 1.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        matrix = glm::lookAt(
            new_pos,
            new_pos + front,
            up
        );
        return matrix;
    }

private:
    float width = get_window_width();
    float height = get_window_height();
    float z_near = 0.1f;
    float z_far = 100.0f;
};
