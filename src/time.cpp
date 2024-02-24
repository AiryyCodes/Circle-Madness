#include "time.h"
#include <GLFW/glfw3.h>

double current = glfwGetTime();
double delta;
double last;

void update_time()
{
    current = glfwGetTime();
    delta = current - last;
    last = current;
}

double get_delta_time()
{
    return delta;
}
