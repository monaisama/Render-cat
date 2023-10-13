#include <stdio.h>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
int main()
{
    glfwInit();
    glewInit();
#ifdef TEST
    printf("hello TEST macro.\n");
#endif

#ifdef DEBUG
    printf("DEBUG\n");
#endif
    printf("hello xmake.");
    return 0;
}