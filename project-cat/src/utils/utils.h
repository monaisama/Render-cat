#pragma once
#include "core/asset.h"
#include "mat/mat.h"

namespace KCore::KUtils
{

KShaderMeta MakeMetaShader(std::string_view, KShaderType);
KMatMeta MakeMetaMat(const KShaderMeta&, const KShaderMeta&);

}
