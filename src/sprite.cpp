#include "sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/gl.h>
#include <cstdio>

Sprite create_sprite(std::string texture_path)
{
    int width;
    int height;
    int channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texture_path.c_str(), &width, &height, &channels, 0);

    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture. %s", texture_path.c_str());
    }

    stbi_image_free(data);

    Texture texture{};
    texture.id = texture_id;
    texture.width = width;
    texture.height = height;
    texture.channels = channels;

    Sprite sprite{};
    sprite.texture = texture;
    sprite.texture_path = texture_path;

    return sprite;
}
