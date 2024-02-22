#include "window.h"
#include "game.h"
#include "input.h"

#include <cstdio>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

bool window_init(const char* title, int width, int height)
{
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW.\n");
        return false;
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        printf("Could not create the GLFW window\n");
        glfwTerminate();
        return false;
    } 

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        printf("Failed to initialize OpenGL context.\n");
        return false;
    }

    if (!game_init())
    {
        printf("Failed to initialize the game.\n");
        return false;
    }

    return true;
}

void window_tick()
{
    while (!glfwWindowShouldClose(window))
    {
        game_update(0);

        glfwSwapBuffers(window);
    
        game_render();

        glfwPollEvents();
    }
}

void window_cleanup()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
