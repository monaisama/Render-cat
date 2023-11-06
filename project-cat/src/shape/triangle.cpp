#include "triangle.h"
#include "utils/utils.h"

namespace KCore
{

void KTriangle::SetupShape()
{
    metaInfo.vertexs = {
        0.f, 0.5f, 0.f,
        0.5f, -0.5f, 0.f,
        -0.5f, -0.5f, 0.f,
    };

    metaInfo.colors = {
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    };

    metaInfo.mat = KUtils::MakeMetaMat(
        KUtils::MakeMetaShader("triangle.vs", KShaderType::Vertex),
        KUtils::MakeMetaShader("triangle.fs", KShaderType::Fragment)
    );
}

}