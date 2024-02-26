#include "font_renderer.h"
#include "camera.h"
#include "game.h"
#include "shader.h"
#include "window.h"

#include <glad/gl.h>
#include <cstdio>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <ft2build.h>
#include <map>
#include <string>
#include FT_FREETYPE_H

unsigned int font_vao;
unsigned int font_vbo;

std::map<char, FontRenderer::Character> characters{};

void FontRenderer::init(Shader& shader)
{
    Camera* camera = get_current_scene().get_node<Camera>();
    //glm::mat4 projection = camera->get_proj_matrix();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(get_window_width()), 0.0f, static_cast<float>(get_window_height()));
    bind_shader(shader);
    set_uniform(shader, "projection", projection);

    FT_Library library;
    if (FT_Init_FreeType(&library))
    {
        printf("Failed to initialize the FreeType library.\n");
        return;
    }
    
    FT_Face face;
    if (FT_New_Face(library, this->font_path, 0, &face))
    {
        printf("Failed to load font: %s\n", this->font_path);
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            printf("Failed to load glyph.\n");
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //printf("Glyph Advance: %i\n", face->glyph->advance.x);

        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        characters.insert(std::pair<char, Character>(c, character));
        //printf("Character Advance 1: %i\n", characters[c].advance);
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(library);

    for (auto const &character : characters)
    {
        //printf("Character Advance 2: %i\n", character.second.advance);
    }

    glGenVertexArrays(1, &font_vao);
    glGenBuffers(1, &font_vbo);
    glBindVertexArray(font_vao);
    glBindBuffer(GL_ARRAY_BUFFER, font_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW); 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    printf("Initialized font.\n");

    //printf("Characters: %i\n", characters.size());
}


void FontRenderer::render(Shader& shader)
{
    glm::mat4 proj_matrix = get_current_scene().get_node<Camera>()->get_proj_matrix();

    bind_shader(shader);
    //set_uniform(shader, "projection", proj_matrix);
    set_uniform(shader, "text_color", this->color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(font_vao);

    int x = parent->get_position().x;

    //if (characters.size() <= 0)
    //    printf("No characters found\n");

    for (auto const &character : characters)
    {
        //printf("Character Advance 3: %i\n", character.second.advance);
    }

    std::string::const_iterator c;
    for (c = this->text.begin(); c != this->text.end(); c++)
    {
        //printf("Char: %c\n", *c);
        Character character = characters[*c];
        //printf("Character: %s\n", character);
        //printf("Character Advance: %i\n", characters[*c].advance);

        float x_pos = x + character.bearing.x * size;
        float y_pos = parent->get_position().y + (character.bearing.y - character.bearing.y) * size; 
        
        float w = character.size.x * size;
        float h = character.size.y * size;
       
        float vertices[6][4] = {
            { x_pos,     y_pos + h,   0.0f, 0.0f },            
            { x_pos,     y_pos,       0.0f, 1.0f },
            { x_pos + w, y_pos,       1.0f, 1.0f },

            { x_pos,     y_pos + h,   0.0f, 0.0f },
            { x_pos + w, y_pos,       1.0f, 1.0f },
            { x_pos + w, y_pos + h,   1.0f, 0.0f }           
        };
        // float vertices[6][4] = {
        //     { x_pos, y_pos, 0.0f, 1.0f },            
        //     { x_pos, y_pos - h, 0.0f, 0.0f },
        //     { x_pos + w, y_pos - h, 1.0f, 0.0f },
        //     { x_pos, y_pos, 0.0f, 1.0f },
        //     { x_pos + w, y_pos - h, 1.0f, 0.0f },
        //     { x_pos + w, y_pos, 1.0f, 1.0f }           
        // };
        // float vertices[6][4] = {
        //     { x_pos, y_pos, 0.0f, 1.0f },
        //     { x_pos + w, y_pos, 1.0f, 1.0f },
        //     { x_pos, y_pos - h, 0.0f, 0.0f },
        //     { x_pos, y_pos - h, 0.0f, 0.0f },
        //     { x_pos + w, y_pos, 1.0f, 1.0f },
        //     { x_pos + w, y_pos - h, 1.0f, 0.0f }
        // };

        //printf("Font Texture ID: %i\n", character.texture_id);
        //printf("Font Bearing X: %i\n", character.bearing.x);

        glBindTexture(GL_TEXTURE_2D, character.texture_id);
        glBindBuffer(GL_ARRAY_BUFFER, font_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (character.advance >> 6) * size;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    //unbind_shader();
}

void FontRenderer::set_text(std::string text)
{
    this->text = text;
}
