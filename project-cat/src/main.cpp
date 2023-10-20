#include <stdio.h>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "kmath.h"

void cat_window_resize(GLFWwindow* window, int32_t width, int32_t height)
{
    glViewport(0, 0, width, height);
}

void cat_window_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "project-cat", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (auto err = glewInit() != GLEW_OK)
    {
        printf("get gl function error. %s", glewGetErrorString(err));
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetWindowSizeCallback(window, cat_window_resize);

    while (!glfwWindowShouldClose(window))
    {
        cat_window_input(window);

        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    printf("close project-cat.");
    return 0;
}