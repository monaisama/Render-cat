#pragma once

#include "core/asset.h"

namespace KCore
{

struct KTextureMeta : IMeta
{
    std::string filePath;
};

class KTexture : public KAsset
{
public:
    virtual const KTextureMeta* GetMeta() const override { return &metaInfo; }

    virtual ~KTexture();

protected:
    KTextureMeta metaInfo;
};

}