#pragma once
#include "core/core.h"
#include "core/asset.h"

namespace KCore
{

enum class KShaderType : uint32_t
{
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER,
    // other 细分着色？
};

struct KShaderMeta : IMeta
{
    std::string filePath;
    KShaderType type;
};

class KShader : public KAsset
{
public:
    KShader(const KShaderMeta&, const std::string&);

    virtual ~KShader();

    GLuint GetShader() const;
    GLenum GetGLShaderType() const { return static_cast<GLenum>(metaInfo.type); }

    virtual const KShaderMeta* GetMeta() const override { return &metaInfo; }

protected:
    GLuint shaderObjectID;

    GLchar logInfo[512];

    KShaderMeta metaInfo;
};

}
