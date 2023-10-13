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
    glewInit();

#ifdef DEBUG
    printf("DEBUG\n");
#endif
    printf("hello xmake.");

    printf("hello year: %d", k_pow(func()));
    return 0;
}