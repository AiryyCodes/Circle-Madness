#pragma once

struct GLFWwindow;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_pos_callback(GLFWwindow* window, double x, double y);

bool is_key_down(int key);
bool is_key_just_down(int key);

bool is_button_down(int button);
bool is_button_just_down(int button);

double get_mouse_x();
double get_mouse_y();
