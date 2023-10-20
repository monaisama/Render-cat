#include <stdio.h>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "kmath.h"

int32_t func()
{
    return 1993;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
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

#ifdef DEBUG
    printf("DEBUG\n");
#endif
    printf("hello xmake.");

    printf("hello year: %d", k_pow(func()));
    return 0;
}