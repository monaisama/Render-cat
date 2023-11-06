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

}