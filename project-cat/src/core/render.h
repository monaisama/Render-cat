#pragma once

#include "core.h"
#include "camera.h"

namespace KCore
{

struct KRenderContext
{
    KMath::KMatrix4f vpMatrix; // �������굽�ü��ռ�����ת��
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