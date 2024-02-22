#include "game.h"
#include "input.h"
#include <GLFW/glfw3.h>
#include <cstdio>

bool game_init()
{
    return true;
}

void game_update(double dt)
{
    if (is_key_down(GLFW_KEY_A))
    {
        printf("A is down\n");
    }

    if (is_key_just_down(GLFW_KEY_S))
    {
        printf("S was just pressed\n");
    }
}

void game_render()
{

}

void game_cleanup()
{

}
