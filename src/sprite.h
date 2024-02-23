#pragma once

#include <string>

struct Texture
{
    unsigned int id;

    int width;
    int height;
    int channels;
};

struct Sprite
{
    Texture texture;
    std::string texture_path;
};

Sprite create_sprite(std::string texture_path);
