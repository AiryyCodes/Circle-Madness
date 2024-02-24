#include "input.h"

#include <GLFW/glfw3.h>

struct GLFWwindow;

bool keys[GLFW_KEY_LAST];
bool keys_held[GLFW_KEY_LAST];

bool buttons[GLFW_MOUSE_BUTTON_LAST];
bool buttons_held[GLFW_MOUSE_BUTTON_LAST];

double mouse_x;
double mouse_y;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keys[key] = action == GLFW_PRESS;
    keys_held[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    buttons[button] = action == GLFW_PRESS;
    buttons_held[button] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

void cursor_pos_callback(GLFWwindow *window, double x, double y)
{
    mouse_x = x;
    mouse_y = y;
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

bool is_button_down(int button)
{
    return buttons_held[button];
}

bool is_button_just_down(int button)
{
    bool state = buttons[button];
    buttons[button] = false;
    return state;
}

double get_mouse_x()
{
    return mouse_x;
}

double get_mouse_y()
{
    return mouse_y;
}
