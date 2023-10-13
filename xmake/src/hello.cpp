#include <stdio.h>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

int32_t func()
{
    return 1993;
}

int main()
{
    glfwInit();
    glewInit();

#ifdef DEBUG
    printf("DEBUG\n");
#endif
    printf("hello xmake.");

    printf("hello year: %d", func());
    return 0;
}