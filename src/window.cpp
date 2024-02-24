#include "window.h"
#include "game.h"
#include "input.h"
#include "time.h"

#include <cstdio>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

int window_width;
int window_height;

int framebuffer_width;
int framebuffer_height;

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
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        window_width = width;
        window_height = height;

        glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
    });

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        printf("Failed to initialize OpenGL context.\n");
        return false;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    
        update_time();

        glViewport(0, 0, window_width, window_height);

        game_update();
        
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

int get_framebuffer_width()
{
    return framebuffer_width;
}

int get_framebuffer_height()
{
    return framebuffer_height;
}
