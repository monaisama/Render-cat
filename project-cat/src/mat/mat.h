#pragma once
#include "core/core.h"

#include "shader.h"
#include "vecs/vec3.h"

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
    void SetBool(const std::string &name, bool value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetInt(const std::string &name, int32_t value) const;
    void SetVec3f(const std::string &name, KMath::KVec3f value) const;

protected:
    GLuint matObjectID;

    GLchar logInfo[512];

    KMatMeta MetaInfo;
};

}