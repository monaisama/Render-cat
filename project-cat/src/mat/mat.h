#pragma once
#include "core/core.h"

#include "shader.h"
#include "vec.h"

namespace KCore
{

struct KShaderPair
{
    std::shared_ptr<KShader> vertexShader;
    std::shared_ptr<KShader> fragmentShader;
};

struct KMatMeta : IMeta
{
    std::optional<std::string> file;
    // or
    std::optional<KShaderMeta> vertexShader;
    std::optional<KShaderMeta> fragmentShader;
};

class KMat : public KAsset
{
public:
    KMat(const KMatMeta&, const KShaderPair&);

    virtual ~KMat();

    void Use() const;

    virtual const KMatMeta* GetMeta() const override { return &metaInfo; }
    void SetBool(const std::string &name, bool value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetInt(const std::string &name, int32_t value) const;
    void SetVec3f(const std::string &name, KMath::KVec3f value) const;

protected:
    GLuint matObjectID;

    GLchar logInfo[512];

    KMatMeta metaInfo;
};

}