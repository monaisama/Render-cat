#include "resource.h"
#include "mat/mat.h"
#include "mat/shader.h"
#include "mat/texture.h"
#include <filesystem>
#include "log.h"

namespace KCore
{

template<>
std::shared_ptr<KShader> KResouces::Load(std::string_view filePath)
{
    if (auto asset = TryFindResource(filePath))
        return std::dynamic_pointer_cast<KShader>(asset);
    
    return nullptr;
} 

template<>
std::shared_ptr<KMat> KResouces::Load(std::string_view filePath)
{
    if (auto asset = TryFindResource(filePath))
        return std::dynamic_pointer_cast<KMat>(asset);
    return nullptr;
}

template<>
std::shared_ptr<KTexture> KResouces::Load(std::string_view filePath)
{
    if (auto asset = TryFindResource(filePath))
        return std::dynamic_pointer_cast<KTexture>(asset);
    {
        using namespace std::filesystem;
        if (!exists(path{filePath}))
        {
            KLog::LogWarning("load image failed. {0} is not exist.", filePath);
            return nullptr;
        }
    }
    return nullptr;
}

std::shared_ptr<KAsset> KResouces::TryFindResource(std::string_view filePath)
{
    std::string path{filePath};
    if (auto iter = assets.find(path); iter != assets.end())
        return iter->second;
    else
        return nullptr;
}

}