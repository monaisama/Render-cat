#pragma once
#include "core/core.h"

#include "shader.h"

namespace KCore::Shader
{

struct KShaderPair
{
    KShader vertexShader;
    KShader fragmentShader;
};

struct KMatMeta : IMeta
{
    std::string vertexFile;
    std::string fragmentFile;
};

class KMat : public KObject
{
public:
    explicit KMat(const KShaderPair&);
    explicit KMat(const KMatMeta&);
    explicit KMat(const KShader& vertexShader, const KShader& fragmentShader);
    virtual ~KMat();

    void Use() const;

    virtual const KMatMeta* GetMeta() const override { return &MetaInfo; }

protected:
    GLuint matObjectID;

    GLchar logInfo[512];

    KMatMeta MetaInfo;
};

}