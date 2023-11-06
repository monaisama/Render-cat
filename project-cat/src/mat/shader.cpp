#include "shader.h"
#include "file.h"
#include "log.h"
#include <string_view>

using namespace KFileUtils;

namespace KCore
{

KShader::KShader(const KShaderMeta& meta, const std::string& content)
{
    metaInfo = meta;
    
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
                metaInfo.filePath, metaInfo.type == KShaderType::Fragment ? "fragment" : "vertex", logInfo);
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

}