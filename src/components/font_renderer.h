#pragma once

#include "../component.h"
#include "shader.h"

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <string>

class FontRenderer : public Component
{
public:
    FontRenderer(std::string text, glm::vec3 color, const char* font_path, int size)
    {
        this->text = text;
        this->color = color;
        this->font_path = font_path;
        this->size = size;
    }

    void init(Shader& shader);
    void render(Shader& shader);
    void cleanup();
    
    void set_text(std::string text);

    struct Character
    {
        unsigned int texture_id;
        glm::ivec2 size;
        glm::ivec2 bearing;
        unsigned int advance;
    };

private:
    std::string text;
    glm::vec3 color;
    const char* font_path;
    int size; 
};
