#include "shader.h"
#include "file.h"
#include "log.h"

KShader::KShader(const GLchar* filePath, KShaderType type)
{
    const GLchar* shaderSource = KFile::ReadFile(filePath).c_str();
    shaderType = static_cast<GLenum>(type);
    shaderObjectID = glCreateShader(GetGLShaderType());
    glShaderSource(shaderObjectID, 1, &shaderSource, nullptr);
    glCompileShader(shaderObjectID);
    {
        GLint success;
        glGetShaderiv(shaderObjectID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderObjectID, 512, nullptr, logInfo);
            KLog::Log(logInfo);
            glDeleteShader(shaderObjectID);
        }
    }
}

KShader::~KShader()
{
    if (glIsShader(shaderObjectID) != GL_FALSE)
        glDeleteShader(shaderObjectID);
}

GLuint KShader::GetShader() const
{
    return shaderObjectID;
}

GLenum KShader::GetGLShaderType() const
{
    return shaderType;
}