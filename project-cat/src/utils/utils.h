#pragma once
#include "core/asset.h"
#include "mat/mat.h"
#include "mat/texture.h"

namespace KCore::KUtils
{

KShaderMeta MakeMetaShader(std::string_view, KShaderType);

KMatMeta MakeMetaMat(const KShaderMeta&, const KShaderMeta&);

KTextureMeta MakeMetaTexture(std::string_view, ETextureSampleType, ETextureWrapMode, EColorType); // 简易版

}
