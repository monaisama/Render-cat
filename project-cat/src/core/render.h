#pragma once

#include "core.h"
#include "camera.h"

namespace KCore
{

struct KRenderContext
{
    KMath::KMatrix4f vpMatrix; // 世界坐标到裁剪空间坐标转换
};

class KRender : public KObject
{
public:
    KRender(const KMath::KCamera&);

    const KRenderContext& GetContext() const { return context; }

protected:
    KRenderContext context;
};

}