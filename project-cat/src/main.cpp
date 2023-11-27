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

#include <string>
#include <map>

// 这里直接写在这里省事 嘻嘻
using namespace KCore;
using namespace KMath;

struct
{
    int32_t windowWidth = 800;
    int32_t windowHeight = 600;

    bool bFirstUpdate = true;

    float deltaTime;
} globalContext {};

struct
{
    double mouseX;
    double mouseY;
    double lastMouseX;
    double lastMouseY;

    bool bfirstMouseUpdate = true;
    float movementSpeed = 2.5f;
    float sensitivity = 0.01f;

    std::map<int32_t, float> keyValue{
        { GLFW_KEY_A, 0.f },
        { GLFW_KEY_S, 0.f },
        { GLFW_KEY_W, 0.f },
        { GLFW_KEY_D, 0.f }
    };

} movementContext { };

KVec2f GetMoveDelta(float deltaTime)
{
    static std::map<int32_t, KVec2f> scales {
        { GLFW_KEY_A, { -1.f, 0.f } },
        { GLFW_KEY_S, { 0.f, -1.f } },
        { GLFW_KEY_W, { 0.f, 1.f } },
        { GLFW_KEY_D, { 1.f, 0.f } }
    };
    KVec2f move{};
    for (const auto& scale : scales)
    {
        if (auto it = movementContext.keyValue.find(scale.first); it != movementContext.keyValue.end())
        {
            move += scale.second * it->second * deltaTime * movementContext.movementSpeed;
        }
    }
    return move;
}

KVec2f GetMouseDelta(float deltaTime)
{
    return {
        static_cast<float>(movementContext.mouseX - movementContext.lastMouseX) * movementContext.sensitivity,
        static_cast<float>(movementContext.mouseY - movementContext.lastMouseY) * movementContext.sensitivity
    };
}

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
    for (auto& key : movementContext.keyValue)
    {
        if (glfwGetKey(window, key.first) == GLFW_PRESS)
            key.second = 1.f;
        else
            key.second = 0.f;
    }
}

void WindowMouse(GLFWwindow* window, double mouseX, double mouseY)
{
    if (movementContext.bfirstMouseUpdate)
    {
        movementContext.lastMouseX = mouseX;
        movementContext.lastMouseY = mouseY;
        movementContext.bfirstMouseUpdate = false;
    }
    else
    {
        movementContext.lastMouseX = movementContext.mouseX;
        movementContext.lastMouseY = movementContext.mouseY;
    }

    movementContext.mouseX = mouseX;
    movementContext.mouseY = mouseY;
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
        KLog::LogError("glewInit Failed. errorcode: {0}", err);
        return -1;
    }

    glViewport(0, 0, globalContext.windowWidth, globalContext.windowHeight);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowSizeCallback(window, WindowResize);
    glfwSetCursorPosCallback(window, WindowMouse);

    float curTime = glfwGetTime();

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
    KCameraTransformer transformer(mainCamera);
    while (!glfwWindowShouldClose(window))
    {
        globalContext.deltaTime = glfwGetTime() - curTime;
        curTime = glfwGetTime();

        WindowInput(window);
        auto moveDelta = GetMoveDelta(globalContext.deltaTime);
        auto mosueDelta = GetMouseDelta(globalContext.deltaTime);
        transformer.MoveForward(moveDelta.Y());
        transformer.MoveRight(moveDelta.X());
        transformer.RotatePitch(mosueDelta.Y());
        transformer.RotateYaw(mosueDelta.X());

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        KRender render(mainCamera);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // example.Render(render);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // triangle.Render(render);
        // triangles2.Render(render);
        exercise.Render(render);

        glfwPollEvents();
        glfwSwapBuffers(window);

        globalContext.bFirstUpdate = false;
    }

    glfwTerminate();
    KLog::Log("project-cat closed.");
    return 0;
}
