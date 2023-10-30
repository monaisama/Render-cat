#include "mat.h"
#include "log.h"

namespace KCore::Shader
{

KMat::KMat(const KShaderPair& shaders)
{
    MetaInfo.vertexFile = shaders.vertexShader.GetMeta()->filePath;
    MetaInfo.fragmentFile = shaders.fragmentShader.GetMeta()->filePath;

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

KMat::KMat(const KMatMeta& Meta)
    : KMat(KShaderPair { KShader(Meta.vertexFile, KShaderType::Vertex), KShader(Meta.vertexFile, KShaderType::Fragment) })
{
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

}