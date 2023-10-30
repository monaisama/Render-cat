#pragma once
#include "core/core.h"
#include "shape/primitive.h"

using namespace KCore;
using namespace KCore::Shape;

class _2Triangles : public KPrimitive
{
protected:
    virtual void SetupShape() override
    {
        MetaInfo.vertexs = {
            -0.5f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            0.5f, 0.5f, 0.f,
            -0.5, 0.5f, 0.f
        };

        MetaInfo.colors = {
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 0.f, 1.f,
            1.f, 1.f, 1.f
        };

        MetaInfo.indices = {
            0,1,2,
            0,2,3
        };

        MetaInfo.Mat.vertexFile = "triangle.vs";
        MetaInfo.Mat.fragmentFile = "triangle.fs";
    }
};