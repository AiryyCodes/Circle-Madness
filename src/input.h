#pragma once

struct GLFWwindow;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool is_key_down(int key);
bool is_key_just_down(int key);
