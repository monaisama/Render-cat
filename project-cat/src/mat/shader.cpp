#include "shader.h"
#include "file.h"
#include "log.h"

using namespace KFileUtils;

namespace KCore::Shader
{

KShader::KShader(const GLchar* filePath, KShaderType type)
{
    MetaInfo.filePath = filePath;
    MetaInfo.type = type;

    std::string content = KFile::ReadFile(filePath); // 这里不能让string 销毁掉
    const GLchar* shaderSource = content.data();
    shaderObjectID = glCreateShader(GetGLShaderType());
    glShaderSource(shaderObjectID, 1, &shaderSource, nullptr);
    glCompileShader(shaderObjectID);
    {
        GLint success;
        glGetShaderiv(shaderObjectID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderObjectID, 512, nullptr, logInfo);
            KLog::LogError("Shader compile failed. filePath: {0}, type: {1}, info: {2}",
                filePath, type == KShaderType::Fragment ? "fragment" : "vertex", logInfo);
            glDeleteShader(shaderObjectID);
        }
    }
}

KShader::KShader(const std::string& filePath, KShaderType type)
    : KShader(filePath.c_str(), type)
{}

KShader::KShader(const KShaderMeta& Meta)
    : KShader(Meta.filePath, Meta.type)
{
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

}