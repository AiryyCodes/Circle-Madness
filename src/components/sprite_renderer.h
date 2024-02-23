#pragma once

#include "../component.h"
#include "../sprite.h"

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(Sprite sprite)
    {
        this->sprite = sprite;
    }

    void init();
    void render();
    void cleanup();

private:
    Sprite sprite;
};
