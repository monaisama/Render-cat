#include "mat.h"
#include "log.h"

namespace KCore
{

KMat::KMat(const KMatMeta& meta, const KShaderPair& pair)
{
    metaInfo = meta;

    matObjectID = glCreateProgram();
    glAttachShader(matObjectID, pair.vertexShader->GetShader());
    glAttachShader(matObjectID, pair.fragmentShader->GetShader());
    glLinkProgram(matObjectID);
    {
        GLint success;
        glGetProgramiv(matObjectID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(matObjectID, 512, nullptr, logInfo);
            KLog::LogError("shader program link failed. info: {0}", logInfo);
            glDeleteProgram(matObjectID);
        }
    }
}

void KMat::SetBool(const std::string& name, bool value) const
{
    SetInt(name, static_cast<int32_t>(value));
}
void KMat::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(matObjectID, name.c_str()), value);
}
void KMat::SetInt(const std::string& name, int32_t value) const
{
    glUniform1i(glGetUniformLocation(matObjectID, name.c_str()), value);
}
void KMat::SetVec3f(const std::string& name, const KMath::KVec3f& value) const
{
    glUniform3f(glGetUniformLocation(matObjectID, name.c_str()), value.X(), value.Y(), value.Z());
}
void KMat::SetMatrix4f(const std::string& name, const KMath::KMatrix4f& value) const
{
    // opengl����������math library������������
    // �������ﲻת�ã���Ϊ��shader������Ҫ��˾��� matrix * vec���Ϳ����ˣ����ת���ˣ�����Ҫ�ҳ˾����� vec * matrix��
    glUniformMatrix4fv(glGetUniformLocation(matObjectID, name.c_str()), 1, GL_FALSE, value.Matrix());
}
void KMat::SetMatrix3f(const std::string& name, const KMath::KMatrix3f& value) const
{
    glUniformMatrix3fv(glGetUniformLocation(matObjectID, name.c_str()), 1, GL_FALSE, value.Matrix());
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