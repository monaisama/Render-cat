#include "utils.h"

namespace KCore::KUtils
{

KShaderMeta MakeMetaShader(std::string_view filePath, KShaderType type)
{
    KShaderMeta meta;
    if (filePath.starts_with("shaders"))
        meta.filePath = filePath;
    else
        meta.filePath = std::string{"shaders/"}.append(filePath);
    meta.type = type;
    return meta; // 这里其实不move 编译器会优化
}

KMatMeta MakeMetaMat(const KShaderMeta& shader1, const KShaderMeta& shader2)
{
    auto selectShader = [&](KShaderType type) -> const KShaderMeta&
    {
        if (shader1.type == type)
            return shader1;
        else //if (shader2.type == type)
            return shader2;
    };

    KMatMeta meta;
    meta.vertexShader = std::make_optional(selectShader(KShaderType::Vertex));
    meta.fragmentShader = std::make_optional(selectShader(KShaderType::Fragment));
    return meta;
}

KTextureMeta MakeMetaTexture(std::string_view filepath, ETextureSampleType sampleType, ETextureWrapMode wrapMode, EColorType colorType)
{
    KTextureMeta meta;
    if (filepath.starts_with("textures"))
        meta.filePath = filepath;
    else
        meta.filePath = std::string{"textures/"}.append(filepath);
    meta.type = ETextureType::Texture2d;
    meta.bAutoMipmap = false;
    meta.sampleTypeMag = sampleType;
    meta.sampleTypeMin = sampleType;
    meta.wrapMode = wrapMode;
    meta.storageColorType = colorType;
    meta.mipmapLevel = 0;
    if (meta.wrapMode == ETextureWrapMode::ClampToBorder)
        meta.borderColor = KColor::white;
    return meta;
}

}