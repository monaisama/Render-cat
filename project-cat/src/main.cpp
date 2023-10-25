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

void TestRender();

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

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        TestRender();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    std::cout << "project-cat closed." << std::endl;
    return 0;
}

void TestRender()
{
    static GLfloat vertices[] = {
        -0.5f, -0.5f, 0.f,
        0.5f, -0.5f, 0.f,
        0.5f, 0.5f, 0.f,
        -0.5, 0.5f, 0.f
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

    GLuint vao;
    glGenVertexArrays(1, &vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
    }
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // exercise 1
    auto _2vao = bindVBOData(_2vertices, sizeof(_2vertices) / sizeof(GLfloat));
    // exercise 2
    auto _2_2_1vao = bindVBOData(_2_2_1vertices, sizeof(_2_2_1vertices) / sizeof(GLfloat));
    auto _2_2_2vao = bindVBOData(_2_2_2vertices, sizeof(_2_2_2vertices) / sizeof(GLfloat));

    auto shaderData = [](const GLchar* const source, uint32_t shaderType) -> GLuint
    {
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        {
            GLint success;
            GLchar infoLog[512];
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 512, nullptr, infoLog);
                std::cout << "ERROR::SHADER::COMPILE_FAILED : " << infoLog << std::endl;
                return 0;
            }
        }
        return shader;
    };

    static const GLchar *vertexShaderSource = " \
    #version 330 core\n  \
    layout (location = 0) in vec3 aPos;\n \
    void main()\n \
    {\n \
        gl_Position = vec4(aPos.xyz, 1.0);\n \
    }\n \
    \0";

    static const GLchar *fragmentShaderSource = " \
    #version 330 core\n \
    out vec4 FragColor;\n \
    void main()\n \
    {\n \
        FragColor = vec4(1.f, 1.f, 1.f, 1.f);\n \
    }\n \
    \0";
    
    // exercise 3
    static const GLchar *_3fragmentShaderSource = " \
    #version 330 core\n \
    out vec4 FragColor;\n \
    void main()\n \
    {\n \
        FragColor = vec4(0.f, 0.f, 1.f, 1.f);\n \
    }\n \
    \0";

    GLuint vertexShader = shaderData(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = shaderData(fragmentShaderSource, GL_FRAGMENT_SHADER);
    GLuint _3fragmentShader = shaderData(_3fragmentShaderSource, GL_FRAGMENT_SHADER);

    auto programData = [](GLuint vertexShader, GLuint fragmentShader) -> GLuint
    {
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        {
            GLint success;
            GLchar infoLog[512];
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED : " << infoLog << std::endl;
                return 0;
            }
        }
        return shaderProgram;
    };

    GLuint shaderProgram = programData(vertexShader, fragmentShader);
    GLuint _3shaderProgram = programData(vertexShader, _3fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(_3fragmentShader);

    glUseProgram(shaderProgram);

    // exercise 1
    glBindVertexArray(_2vao);
    {
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glBindVertexArray(0);

    glUseProgram(shaderProgram);
    // exercise 2
    glBindVertexArray(_2_2_1vao);
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    glUseProgram(_3shaderProgram);
    glBindVertexArray(_2_2_2vao);
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    glBindVertexArray(0);
}