#include "triangle.h"

namespace KCore
{

void KTriangle::SetupShape()
{
    MetaInfo.vertexs = {
        -0.5f, -0.5f, 0.f,
        0.5f, -0.5f, 0.f,
        0.5f, 0.5f, 0.f,
    };

    MetaInfo.colors = {
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    };

    MetaInfo.Mat.vertexFile = "triangle.vs";
    MetaInfo.Mat.fragmentFile = "triangle.fs";
}

}