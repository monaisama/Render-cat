#include "core/core.h"
#include "GLFW/glfw3.h"

#include "mymath.h"
#include "test.h"
#include "log.h"
#include "file.h"
#include "mat/mat.h"
#include "shape/primitive.h"
#include "shape/triangle.h"
#include "exercise/test_shapes.h"

#include "3rd/image.h"

// 这里直接写在这里省事 嘻嘻
using namespace KCore::Shader;
using namespace KCore::Shape;

void WindowResize(GLFWwindow* window, int32_t width, int32_t height)
{
    glViewport(0, 0, width, height);
}

void WindowInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void TestTex()
{
    // uint8_t *data = stbi_load
}

int main()
{
    TestCompileConfig();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "project-cat", nullptr, nullptr);
    if (!window)
    {
        KLog::LogError("glfw window created failed.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (auto err = glewInit() != GLEW_OK)
    {
        KLog::LogError("GlewInit Failed. errorcode: {0}", err);
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetWindowSizeCallback(window, WindowResize);

    KTriangle triangle;
    triangle.Setup();

    K_2Triangles excrise1;
    excrise1.Setup();

    KExcriseShape shape;
    shape.Setup();



    while (!glfwWindowShouldClose(window))
    {
        WindowInput(window);

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        triangle.Render();
        excrise1.Render();
        shape.Render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    KLog::Log("project-cat closed.");
    return 0;
}
