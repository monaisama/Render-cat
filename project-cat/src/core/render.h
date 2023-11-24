#pragma once

#include "core.h"
#include "camera.h"

namespace KCore
{

struct KRenderContext
{
    const KMath::KCamera& camera;
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