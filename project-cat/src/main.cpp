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
#include "camera.h"

#include "resource/resources.h"
#include "3rd/image.h"
#include "utils/utils.h"
#include "mat/texture.h"

// 这里直接写在这里省事 嘻嘻
using namespace KCore;
using namespace KMath;

struct
{
    int32_t windowWidth = 800;
    int32_t windowHeight = 600;
} globalContext;

float GetAspectRatio()
{
    return static_cast<float>(globalContext.windowWidth) / globalContext.windowHeight;
}

void WindowResize(GLFWwindow* window, int32_t width, int32_t height)
{
    globalContext.windowWidth = width;
    globalContext.windowHeight = height;
    glViewport(0, 0, width, height);
}

void WindowInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
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

    glViewport(0, 0, globalContext.windowWidth, globalContext.windowHeight);
    glfwSetWindowSizeCallback(window, WindowResize);

    KTriangle triangle;
    triangle.Setup();

    KExample example;
    example.Setup();

    K_2Triangles triangles2;
    triangles2.Setup();

    KExerciseShape exercise;
    exercise.Setup();

    glEnable(GL_DEPTH_TEST);

    KCamera mainCamera = KCamera::Persp(90.f, 0.1f, 1000.f, GetAspectRatio()).LookAt({-10,0,10}, KVec3f::zero);
    while (!glfwWindowShouldClose(window))
    {
        WindowInput(window);

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        KVec3f newLoc {10 * sinf(glfwGetTime()), 10 * cosf(glfwGetTime()), 10};
        KRender render(mainCamera.LookAt(newLoc, KVec3f::zero));
        
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // example.Render(render);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // triangle.Render(render);
        // triangles2.Render(render);
        exercise.Render(render);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    KLog::Log("project-cat closed.");
    return 0;
}
