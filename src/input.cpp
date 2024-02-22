#include "input.h"

#include <GLFW/glfw3.h>

bool keys[GLFW_KEY_LAST];
bool keys_held[GLFW_KEY_LAST];

struct GLFWwindow;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keys[key] = action == GLFW_PRESS;
    keys_held[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

bool is_key_down(int key)
{
    return keys_held[key];
}

bool is_key_just_down(int key)
{
    bool state = keys[key];
    keys[key] = false;
    return state;
}
