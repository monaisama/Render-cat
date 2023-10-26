#include "mat.h"
#include "log.h"

KMat::KMat(const KShaderPair& shaders)
{
    matObjectID = glCreateProgram();
    glAttachShader(matObjectID, shaders.vertexShader.GetShader());
    glAttachShader(matObjectID, shaders.fragmentShader.GetShader());
    glLinkProgram(matObjectID);
    {
        GLint success;
        glGetProgramiv(matObjectID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(matObjectID, 512, nullptr, logInfo);
            KLog::Log(logInfo);
            glDeleteProgram(matObjectID);
        }
    }
}

KMat::~KMat()
{
    if (glIsProgram(matObjectID) != GL_FALSE)
    {
        glDeleteProgram(matObjectID);
    }
}

void KMat::Use() const
{
    glUseProgram(matObjectID);
}