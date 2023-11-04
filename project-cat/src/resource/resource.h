#pragma once

#include "core/core.h"
#include "core/asset.h"
#include "patterns.h"
#include <string_view>
#include <string>
#include <map>

namespace KCore
{

class KResouces : public KObject
{
    GEN_SINGLETON_CODE(KResouces)

public:
    template<class T>
    requires std::is_base_of_v<KAsset, T>
    std::shared_ptr<T> Load(std::string_view filePath)
    {
        throw std::exception("no support type.");
    }

    template<class TAsset, class TMeta>
    requires std::is_base_of_v<KAsset, TAsset> && std::is_base_of_v<IMeta, TMeta>
    std::shared_ptr<TAsset> Load(TMeta& meta)
    {
        throw std::exception("no support type.");
    }

protected:
    std::shared_ptr<KAsset> TryFindResource(std::string_view filePath); // 路径查找所有
    std::map<std::string, std::shared_ptr<KAsset>> assets;
};
}