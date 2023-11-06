#include "resources.h"
#include "mat/mat.h"
#include "mat/shader.h"
#include "mat/texture.h"
#include <filesystem>
#include "log.h"
#include "file.h"

// 这里用于将来看看怎么定义instance，同一个材质的不同实例
#define MaterialInstance 0

namespace KCore
{

template<>
std::shared_ptr<KShader> KResources::Load(const KShaderMeta& meta)
{
    if (!Validate(meta.filePath))
        return nullptr;
    
    if (auto asset = TryFindResource(meta.filePath))
        return std::dynamic_pointer_cast<KShader>(asset);
    
    std::string content = KFileUtils::KFile::ReadFile(meta.filePath);
    auto shader = std::make_shared<KShader>(meta, content);
    assets[meta.filePath] = shader;
    return shader;
}

template<>
std::shared_ptr<KMat> KResources::Load(std::string_view filePath)
{
    throw std::exception("not support yet.");

    if (!Validate(filePath))
        return nullptr;

    if (auto asset = TryFindResource(filePath))
        return std::dynamic_pointer_cast<KMat>(asset);
    return nullptr;
}

template<>
std::shared_ptr<KMat> KResources::Load(const KMatMeta& meta)
{
    if (!meta.fragmentShader.has_value() || !meta.vertexShader.has_value())
    {
        KLog::LogSimpleError("Material's metainfo not set correctly");
        return nullptr;
    }
    if (!Validate(meta.vertexShader.value().filePath) || !Validate(meta.fragmentShader.value().filePath))
        return nullptr;

#if MaterialInstance
    auto matIndex = std::string{meta.vertexShader.value().filePath}.append("_").append(meta.fragmentShader.value().filePath); // 性能不管了 todo..
    if (auto asset = TryFindResource(matIndex))
        return std::dynamic_pointer_cast<KMat>(asset);
#endif
    
    auto vertexShader = Load<KShader>(meta.vertexShader.value());
    auto fragmentShader = Load<KShader>(meta.fragmentShader.value());

    auto mat = std::make_shared<KMat>(meta, KShaderPair{ vertexShader, fragmentShader });

#if MaterialInstance
    assets[matIndex] = mat;
#endif

    return mat;
}

template<>
std::shared_ptr<KTexture> KResources::Load(std::string_view filePath)
{
    throw std::exception("not support yet.");

    if (!Validate(filePath))
        return nullptr;
        
    if (auto asset = TryFindResource(filePath))
        return std::dynamic_pointer_cast<KTexture>(asset);
    return nullptr;
}

template<>
std::shared_ptr<KTexture> KResources::Load(const KTextureMeta& meta)
{
    return Load<KTexture>(meta.filePath);
}

std::shared_ptr<KAsset> KResources::TryFindResource(std::string_view filePath)
{
    std::string path{filePath};
    if (auto iter = assets.find(path); iter != assets.end())
        return iter->second;
    else
        return nullptr;
}

bool KResources::Validate(std::string_view filePath)
{
    using namespace std::filesystem;
    if (!exists(path{filePath}))
    {
        KLog::LogSimpleError("load file is not exists.", filePath);
        return false;
    }
    return true;
}

}