#include "window.h"
#include "game.h"
#include "input.h"

#include <cstdio>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

int window_width;
int window_height;

bool window_init(const char* title, int width, int height)
{
    window_width = width;
    window_height = height;

    if (!glfwInit())
    {
        printf("Failed to initialize GLFW.\n");
        return false;
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        printf("Could not create the GLFW window\n");
        glfwTerminate();
        return false;
    } 

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        window_width = width;
        window_height = height;
    });

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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, window_width, window_height);

        game_update(0);
        
        game_render();
       
        glfwSwapBuffers(window); 
        glfwPollEvents();
    }
}

void window_cleanup()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

int get_window_width()
{
    return window_width;
}

int get_window_height()
{
    return window_height;
}
