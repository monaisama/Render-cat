#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "mymath.h"
#include "test.h"

#include "log.h"
#include "file.h"
#include "mat/mat.h"
#include "shape/primitive.h"
#include "shape/triangle.h"

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

void TestRender(const KMat& defaultMat, const KMat& blueMat);

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
        KLog::Log("glfw window is nullptr. create failed.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (auto err = glewInit() != GLEW_OK)
    {
        KLog::Log(err);
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetWindowSizeCallback(window, WindowResize);

    // KShader defaultVS("default.vs", KShaderType::Vertex);
    // KShader defaultFS("default_color.fs", KShaderType::Fragment), blueFS("blue_color.fs", KShaderType::Fragment);
    // KMat defaultMat(KShaderPair{defaultVS, defaultFS}), blueMat(KShaderPair{defaultVS, blueFS});

    KTriangle triangle;
    triangle.Setup();
    while (!glfwWindowShouldClose(window))
    {
        WindowInput(window);

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // TestRender(defaultMat, blueMat);
        triangle.Render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    KLog::Log("project-cat closed.");
    return 0;
}

void TestRender(const KMat& defaultMat, const KMat& blueMat)
{
    static GLfloat vertices[] = {
        -0.5f, -0.5f, 0.f,
        0.5f, -0.5f, 0.f,
        0.5f, 0.5f, 0.f,
        // -0.5, 0.5f, 0.f
    };

    static GLuint indices[] = {
        0,1,2,
        0,2,3
    };

    // exercise 1
    static GLfloat _2vertices[] = {
        0.f, 0.5f, 0.f,
        0.5f, 0.f, 0.f,
        0.f, -0.5f, 0.f,
        0.f, -0.5f, 0.f,
        -0.5f, 0.f, 0.f,
        0.f, 0.5f, 0.f,
    };

    // exercise 2
    static GLfloat _2_2_1vertices[] = {
        -0.6f, 0.6f, 0.f,
        -0.8f, -0.6f, 0.f,
        -0.4f, -0.6f, 0.f
    };

    static GLfloat _2_2_2vertices[] = {
        0.6f, 0.6f, 0.f,
        0.8f, -0.6f, 0.f,
        0.4f, -0.6f, 0.f
    };

    auto bindVBOData = [](GLfloat vertices[], size_t size) -> GLuint
    {
        GLuint vao, vbo;
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);
        {
            glBindBuffer(GL_ARRAY_BUFFER, vao);
            glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
            glEnableVertexAttribArray(0);
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);

        return vao;
    };

    // GLuint vao;
    // glGenVertexArrays(1, &vao);
    // GLuint vbo;
    // glGenBuffers(1, &vbo);
    // GLuint ebo;
    // glGenBuffers(1, &ebo);

    // glBindVertexArray(vao);
    // {
    //     // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //     // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //     glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    //     glEnableVertexAttribArray(0);
    // }
    // glBindVertexArray(0);
    // glDisableVertexAttribArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 好像这样不重新binding是不行的，那同一个vbo（显存数据）怎么能被不同的vao使用或者，怎么其他的什么东西使用呢？
    // GLuint _test_vao;
    // glGenVertexArrays(1, &_test_vao);
    // glBindVertexArray(_test_vao);
    // {
    //     glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //     glEnableVertexAttribArray(0);
    // }
    // glBindVertexArray(0);
    // glDisableVertexAttribArray(0);

    // exercise 1
    auto _2vao = bindVBOData(_2vertices, sizeof(_2vertices) / sizeof(GLfloat));
    // exercise 2
    auto _2_2_1vao = bindVBOData(_2_2_1vertices, sizeof(_2_2_1vertices) / sizeof(GLfloat));
    auto _2_2_2vao = bindVBOData(_2_2_2vertices, sizeof(_2_2_2vertices) / sizeof(GLfloat));

    defaultMat.Use();
    // glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0);

    // exercise 1
    glBindVertexArray(_2vao);
    {
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glBindVertexArray(0);

    // exercise 2
    glBindVertexArray(_2_2_1vao);
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    blueMat.Use();
    glBindVertexArray(_2_2_2vao);
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    glBindVertexArray(0);

    KTriangle triangle;
    triangle.Setup();
    triangle.Render();
}