#pragma once
#include <cstdint>
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

enum class KShaderType : uint32_t
{
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER,
    // other 细分着色？
};

class KShader
{
public:
    explicit KShader(const GLchar*, KShaderType);
    ~KShader();

    GLuint GetShader() const;
    GLenum GetGLShaderType() const;

protected:
    GLuint shaderObjectID;
    GLenum shaderType;

    GLchar logInfo[512];
};
