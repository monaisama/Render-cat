#pragma once

#include "core/core.h"
#include "core/asset.h"
#include "patterns.h"
#include <string_view>
#include <string>
#include <map>
#include "3rd/image.h"
#include "mat/mat.h"
#include "mat/texture.h"

namespace KCore
{

class KResources : public KObject
{
    GEN_SINGLETON_CODE(KResources)

public:
    template<class T>
    requires std::is_base_of_v<KAsset, T>
    std::shared_ptr<T> Load(std::string_view filePath)
    {
        throw std::exception("no support type.");
    }

    template<class TAsset, class TMeta>
    requires std::is_base_of_v<KAsset, TAsset> && std::is_base_of_v<IMeta, TMeta>
    std::shared_ptr<TAsset> Load(const TMeta& meta)
    {
        throw std::exception("no support type.");
    }

protected:
    bool Validate(std::string_view);

protected:
    std::shared_ptr<KAsset> TryFindResource(std::string_view filePath); // 路径查找所有
    std::map<std::string, std::shared_ptr<KAsset>> assets;
};

template<> std::shared_ptr<KMat> KResources::Load(const KMatMeta&);
template<> std::shared_ptr<KTexture> KResources::Load(const KTextureMeta&);

}