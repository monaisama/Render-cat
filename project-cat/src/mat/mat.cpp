#include "mat.h"
#include "log.h"

namespace KCore::Shader
{

KMat::KMat(const KShaderPair& shaders)
    : KMat(shaders.vertexShader, shaders.fragmentShader)
{

}

KMat::KMat(const KMatMeta& meta)
    : KMat(KShader(meta.vertexFile, KShaderType::Vertex), KShader(meta.fragmentFile, KShaderType::Fragment))
{
}

KMat::KMat(const KShader& vertex, const KShader& fragment)
{
    MetaInfo.vertexFile = vertex.GetMeta()->filePath;
    MetaInfo.fragmentFile = fragment.GetMeta()->filePath;

    matObjectID = glCreateProgram();
    glAttachShader(matObjectID, vertex.GetShader());
    glAttachShader(matObjectID, fragment.GetShader());
    glLinkProgram(matObjectID);
    {
        GLint success;
        glGetProgramiv(matObjectID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(matObjectID, 512, nullptr, logInfo);
            KLog::Log("error: link program: ");
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

}