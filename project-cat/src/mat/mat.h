#pragma once
#include "core/core.h"

#include "shader.h"
#include "vec.h"
#include "matrix.h"

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
    void SetBool(const std::string&, bool) const;
    void SetFloat(const std::string&, float) const;
    void SetInt(const std::string&, int32_t) const;
    void SetVec3f(const std::string&, const KMath::KVec3f&) const;
    void SetMatrix4f(const std::string&, const KMath::KMatrix4f&) const;
    void SetMatrix3f(const std::string&, const KMath::KMatrix3f&) const;

protected:
    GLuint matObjectID;

    GLchar logInfo[512];

    KMatMeta metaInfo;
};

}